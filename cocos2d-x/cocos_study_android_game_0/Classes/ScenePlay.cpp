#include "ScenePlay.h"

#include "Player.h"
#include "CollisionUtils.h"
#include "Boss.h"
#include "ActorManager.h"
#include "PlayMap.h"
#include "MapTile.h"
#include "DataManager.h"
#include "StopWatch.h"

#define ZORDER_MAP 0
#define ZORDER_PLAYER 1
#define ZORDER_ENEMY 5
#define IS_IMMOTAL_PLAYER true
#define	DRAG_DISTANCE 100
#define ROLL_CONTROL_TIME 0.3
#define FOLLOW_RATIO_ENEMY 0.3
#define FOLLOW_RATIO_ARROW 0.43

Scene * ScenePlay::createScene()
{
	auto scene = Scene::create();
	auto play = ScenePlay::create();

	scene->addChild(play);

	return scene;
}

bool ScenePlay::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}
	
	srand(time(nullptr));

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//root
	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);

	//root->uiNode
	mUINode = Node::create();
	mRenderNode->addChild(mUINode, 10);

#pragma region UI

	mUIPadBack = Sprite::create("ui/pad/ui_pad_back.jpg");
	mUIPadBack->setAnchorPoint(Vec2(0.5, 0));
	mUIPadBack->setPosition(Vec2(visibleSize.width*0.5, 0));
	//mUIPadBack->setScale(CC_CONTENT_SCALE_FACTOR());
	mUIPadBack->setColor(Color3B::GRAY);
	mUINode->addChild(mUIPadBack, 0);


	mUIPadFront = Sprite::create("ui/pad/ui_pad_front.png");
	Size uiPadBackSize = mUIPadBack->getContentSize();
	mUIPadFront->setPosition(Vec2(uiPadBackSize.width*0.5, uiPadBackSize.height*0.5));
	//mUIPadFront->setScale(CC_CONTENT_SCALE_FACTOR());
	mUINode->addChild(mUIPadFront, 1);

	mUIPadFrontImage = new Image();
	mUIPadFrontImage->initWithImageFile("ui/pad/ui_pad_front.png");
	mUIPadFrontImage->autorelease();
	mUIPadFrontImage->retain();

	mPadMaxDistance = 3;

	mKillCountBackground = Sprite::create("white4x4.jpg");
	mKillCountBackground->setTextureRect(Rect(0, 0, 720, 140));
	mKillCountBackground->setAnchorPoint(Vec2(0, 0.5));
	mKillCountBackground->setColor(Color3B::BLACK);
	mKillCountBackground->setOpacity(255 * 0.5);
	mKillCountBackground->setPosition(-mKillCountBackground->getContentSize().width, visibleSize.height*0.85);

	mKillCountLabel = Label::createWithTTF("99", "fonts/NotoSansKR-Regular-Hestia.otf", 85);
	mKillCountLabel->setColor(Color3B::WHITE);
	mKillCountLabel->setPosition(
		mKillCountBackground->getContentSize().width*0.5,
		mKillCountBackground->getContentSize().height*0.5);
	mKillCountBackground->addChild(mKillCountLabel);
	


	mUINode->addChild(mKillCountBackground);

#pragma endregion


	mFadeSprite = Sprite::create("white4x4.jpg");
	mFadeSprite->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
	mFadeSprite->setAnchorPoint(Vec2(0, 0));
	mFadeSprite->setColor(Color3B::BLACK);
	this->addChild(mFadeSprite, 10);

	//root->playNode
	mPlayNodeSize = Size(visibleSize.width, visibleSize.height - uiPadBackSize.height);
	mPlayNode = Node::create();
	mPlayNode->setPosition(Vec2(0, uiPadBackSize.height));
	mRenderNode->addChild(mPlayNode, 0);

	mPlayNodeOffsetScalar = 240;
	mPlayNodeOffsetDirection = Vec2::ZERO;

#pragma region Create
	mPlayMap = ActorManager::GetInstance()->GetPlayMap();
	mPlayNode->addChild(mPlayMap, ZORDER_MAP);

	mPlayer = ActorManager::GetInstance()->GetPlayer();
	mPlayNode->addChild(mPlayer, ZORDER_PLAYER);

	mArrow = Arrow::create();
	mArrow->InitWithPlayer(mPlayer);
	mPlayNode->addChild(mArrow, ZORDER_PLAYER + 1);
#pragma endregion
	
#pragma region StopWatch

	mRollStopWatch = StopWatch::create();
	mRollStopWatch->SetAutoUpdate(true);
	this->addChild(mRollStopWatch);

	mShakeStopWatch = StopWatch::create();
	mShakeStopWatch->SetAutoUpdate(true);
	this->addChild(mShakeStopWatch);
#pragma endregion

	mFollowRatio = FOLLOW_RATIO_ENEMY;

	RoomSequence(0);
	
	this->scheduleUpdate();
	return true;
}

void ScenePlay::RoomSequence(int roomIndex, bool isReset)
{
	mCurrentRoomIndex = roomIndex;
	mIsPlaying = false;
	mPlayer->SetIsControl(false);
	mPlayer->SetAlive(true);
	mCameraSecondTarget = nullptr;

	auto mapData = DataManager::GetInstance()->GetMapData(roomIndex);
	if (mapData == nullptr)
	{
		//log("nothing map");
		Director::getInstance()->end();
		return;
	}

	auto tSeq = Sequence::create(
		FadeIn::create(0.15),
		CallFunc::create([this, isReset]()
	{
		auto stageData = DataManager::GetInstance()->GetStageData(mCurrentRoomIndex);

		if (stageData != nullptr)
		{
			if (isReset == false)
			{
				mPlayMap->CreateTiles(mCurrentRoomIndex);

				if (mCurrentEnemy != nullptr)
				{
					mPlayNode->removeChild(mCurrentEnemy);
					mCurrentEnemy = nullptr;
				}
				mCurrentEnemy = ActorManager::GetInstance()->CreateEnemy(stageData->enemy.id);
				mCurrentEnemy->SetCameraFollow(stageData->enemy.cameraFollow);
				mPlayNode->addChild(mCurrentEnemy, ZORDER_ENEMY);
			}

			Vec2 pos;
			pos.x = mPlayMap->GetMapContentSize().width * stageData->enemy.position.x;
			pos.y = mPlayMap->GetMapContentSize().height * stageData->enemy.position.y;
			mCurrentEnemy->setPosition(pos);
			mCurrentEnemy->SetAlive(true);
			mCurrentEnemy->OnActivate(false);
		}
		else
		{
			mPlayMap->CreateTiles(mCurrentRoomIndex);
			if (mCurrentEnemy != nullptr)
			{
				mPlayNode->removeChild(mCurrentEnemy);
				mCurrentEnemy = nullptr;
			}
		}
		DataManager::GetInstance()->SetMapSize(mPlayMap->GetMapContentSize());

		Vec2 initPos;
		initPos.x = mPlayMap->GetMapContentSize().width * 0.5;
		initPos.y = mPlayMap->GetMapContentSize().height * 0.1;
		mPlayer->InitPosition(initPos);

		mArrow->LockOn(Vec2(0, 1), true);

		CalculatePlayNodePosition(1);
	}),
		/*DelayTime::create(0.1),*/
		FadeOut::create(0.15),
		CallFunc::create([this]()
	{
		ShowKillCount();
		mPlayer->SetIsControl(true);
		if (mCurrentEnemy != nullptr)
		{
			mCurrentEnemy->OnActivate(true);
			mCameraSecondTarget = mCurrentEnemy;
		}
		mIsPlaying = true;
	}),
		nullptr
		);
	mFadeSprite->runAction(tSeq);

}

void ScenePlay::onEnter()
{
	LayerColor::onEnter();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ScenePlay::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ScenePlay::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ScenePlay::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void ScenePlay::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	CC_SAFE_RELEASE_NULL(mUIPadFrontImage);

	LayerColor::onExit();
}

void ScenePlay::update(float dt)
{
	if (mIsPlaying == false)
	{
		return;
	}
	//Map Scroll
	CalculatePlayNodePosition(dt * 2);

#pragma region Tile Collision

	mPlayMap->CheckCollisionTile(mArrow, mArrow->GetMoveDirection());
	mPlayMap->CheckCollisionTile(mPlayer, mPlayer->GetMoveDir());

#pragma endregion

#pragma region mArrow State Check

	if (mArrow->GetState() == Arrow::State::State_Shot)
	{
		mUIPadBack->setColor(Color3B::GRAY);
	}
	else
	{
		mUIPadBack->setColor(Color3B::WHITE);
	}
#pragma endregion

#pragma region Enemy Collision

	if (mCurrentEnemy != nullptr)
	{
		mCurrentEnemy->CheckCollisionActor(mArrow);
		if (IS_IMMOTAL_PLAYER == false && mPlayer->GetState() != Player::State::Roll)
		{
			mCurrentEnemy->CheckCollisionActor(mPlayer);
		}
		if (mCurrentEnemy->IsAlive() == false)
		{
			RoomClearSequence();
			return;
		}
	}
#pragma endregion
	if (mPlayer->IsAlive() == false)
	{
		GameOverSequence();
		return;
	}

	mArrow->OnCollisionOther(false, nullptr);
}

void ScenePlay::GameOverSequence()
{
	mIsPlaying = false;
	mPlayer->SetIsControl(false);

	auto gameOverSeq = Sequence::create(
		DelayTime::create(0.3),
		CallFunc::create([this]()
	{
		this->RoomSequence(mCurrentRoomIndex, true);
	}),		
		nullptr
	);
	mPlayNode->runAction(gameOverSeq);
}

void ScenePlay::RoomClearSequence()
{
	//mPlayer->SetIsControl(false);
	mIsPlaying = false;

	auto lastSeq = Sequence::create(
		CallFunc::create([](){
		Director::getInstance()->getScheduler()->setTimeScale(0.3);}),
		DelayTime::create(0.15),
		CallFunc::create([](){
		Director::getInstance()->getScheduler()->setTimeScale(1);}),
		nullptr
		);

	Sequence * clearSeq = nullptr;

	if (DataManager::GetInstance()->GetMapData(mCurrentRoomIndex))
	{
		clearSeq = Sequence::create(
			lastSeq,
			//FadeIn::create(0.15),
			//CallFunc::create([this]() { Director::getInstance()->end(); }),
			CallFunc::create([this]() {this->RoomSequence(mCurrentRoomIndex,true); }),
			nullptr);
		mFadeSprite->runAction(clearSeq);
		mKillCount++;
	}
	else
	{
		clearSeq = Sequence::create(
			lastSeq,
			CallFunc::create([this](){this->RoomSequence(mCurrentRoomIndex + 1);}),
			nullptr);
		mPlayNode->runAction(clearSeq);

	}

	
	
}

void ScenePlay::ShowKillCount()
{
	mKillCountLabel->setString(StringUtils::format("%d", mKillCount));
	mKillCountBackground->runAction(
		Sequence::create(
			EaseExponentialInOut::create(MoveTo::create(1.3, Vec2(0, mKillCountBackground->getPosition().y))),
			DelayTime::create(0.15),
			EaseExponentialInOut::create(MoveTo::create(1.3, Vec2(-mKillCountBackground->getContentSize().width, mKillCountBackground->getPosition().y))),
			//EaseQuinticActionOut::create(RotateBy::create(1.8, Vec3(360*4,0,0))),
			nullptr));
}

void ScenePlay::CalculatePlayNodePosition(float dt)
{
	Vec2 targetPos;

	if (mCameraTarget == nullptr)
	{
		targetPos = mPlayer->getPosition();
	}
	else
	{
		targetPos = mCameraTarget->getPosition();
	}

	if (mCameraSecondTarget != nullptr/* && mCurrentEnemy->IsCameraFollow()*/)
	{
		Vec2 dist = mCameraSecondTarget->getPosition() - targetPos;
		targetPos += dist * mFollowRatio;
	}

	Vec2 pos;

	Vec2 origin;
	origin.x = (mPlayNodeSize.width * 0.5);
	origin.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;

	pos = (origin - targetPos) + Vec2(-mPlayNodeOffsetDirection.x * mPlayNodeOffsetScalar, -mPlayNodeOffsetDirection.y * mPlayNodeOffsetScalar);

	pos.y = MIN(pos.y, mUIPadBack->getContentSize().height);

	pos = ccpLerp(mPlayNode->getPosition(), pos, dt);

	if (mIsCameraShake)
	{
		/*float duration = 0.2;
		float shake = sin((mShakeStopWatch->GetAccTime() / duration)*10.0f) * powf(0.5f, (mShakeStopWatch->GetAccTime() / duration));
		pos.x += 3 * shake;*/
	}
		
	mPlayNode->setPosition(pos);
}


bool ScenePlay::onTouchBegan(Touch * touch, Event * unused_event)
{
	if (mPlayer->GetIsControl() == false)
	{
		return false;
	}

	bool isTouchMoved = false;
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());
	if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
	{
		if (mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
			CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos))//move
		{
			mTouchBeganPos = convertToWorldSpace(mUIPadFront->getPosition());
			mTouchState = TouchState::Move;
			isTouchMoved = true;
			//roll timer start
			mRollStopWatch->OnStart();
			float gray = 240;
			mUIPadFront->setColor(Color3B(gray, gray, gray));
		}
		else if(mArrow->GetState() != Arrow::State::State_Drop)//attack
		{
			if (mArrow->GetState() != Arrow::State::State_Shot)
			{
				mTouchBeganPos = touch->getLocation();
				mTouchState = TouchState::Shot;
				Vec2 dir = mTouchBeganPos - convertToWorldSpace(mUIPadFront->getPosition());
				mArrow->LockOn(dir.getNormalized());
				isTouchMoved = true;
			}
		}
		else//ArrowDrop...
		{
			mArrow->SetReturnArrow(true);
			mTouchState = TouchState::Collect;
			isTouchMoved = true;

			//camera shake, camera follow to arrow
			mIsCameraShake = true;
			mShakeStopWatch->OnStart();

			mCameraSecondTarget = mArrow;
			mFollowRatio = FOLLOW_RATIO_ARROW;
		}
		//isTouchMoved = true;
	}


	return isTouchMoved;
}

void ScenePlay::onTouchMoved(Touch * touch, Event * unused_event)
{
	Vec2 touchPos = touch->getLocation();
	touchPos.clamp(Vec2::ZERO, mUIPadBack->getContentSize());
	Vec2 dir;

	switch (mTouchState)
	{
	case TouchState::Move:
		dir = touchPos - mTouchBeganPos;

		dir.x = clampf(dir.x / 60, -1, 1);
		dir.y = clampf(dir.y / 60, -1, 1);

		mPlayer->SetMoveDir(dir);

		mArrow->LockOn(dir.getNormalized());

		break;
	case TouchState::Shot:
		dir = mTouchBeganPos - touchPos;

		mArrow->LockOn(dir.getNormalized());

		if (mTouchBeganPos.distance(touchPos) > DRAG_DISTANCE)
		{
			mPlayNodeOffsetDirection = dir.getNormalized();
		}
		else
		{
			mPlayNodeOffsetDirection = Vec2::ZERO;
		}
		break;
	}
}

void ScenePlay::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());

	switch (mTouchState)
	{
	case TouchState::Shot:
		if (mTouchBeganPos.distance(touchPos) > DRAG_DISTANCE)
		{
			mArrow->Shot();
		}
		mPlayNodeOffsetDirection = Vec2::ZERO;
		break;
	case TouchState::Move:
		if (mRollStopWatch->OnStop() <= ROLL_CONTROL_TIME
			|| !(mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
				CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
		{
			Vec2 dir = touch->getLocation() - mTouchBeganPos;
			float endedRadian = atan2(dir.y, dir.x);
			mPlayer->OnRoll(endedRadian);
		}
		mArrow->DisableLockOn();
		mUIPadFront->setColor(Color3B::WHITE);
		break;
	case TouchState::Collect:
		mArrow->SetReturnArrow(false);
		mCameraSecondTarget = mCurrentEnemy;

		//disable shake,camera follow
		mIsCameraShake = false;
		mShakeStopWatch->OnStop();

		mCameraSecondTarget = mCurrentEnemy;
		mFollowRatio = FOLLOW_RATIO_ENEMY;
		
		break;
	}


	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

}

