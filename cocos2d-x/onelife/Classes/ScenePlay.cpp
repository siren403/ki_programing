#include "ScenePlay.h"

#include "Player.h"
#include "CollisionUtils.h"
#include "Boss.h"
#include "ActorManager.h"
#include "PlayMap.h"
#include "MapTile.h"
#include "DataManager.h"
#include "StopWatch.h"
#include "SceneTitle.h"
#include "SWDrawCircle.h"
#include "EffectEnemyKill.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define ZORDER_MAP 0
#define ZORDER_PLAYER 1
#define ZORDER_ENEMY 5
#define IS_IMMOTAL_PLAYER false
#define	DRAG_DISTANCE 100
#define ROLL_CONTROL_TIME 0.3
#define FOLLOW_RATIO_ENEMY 0.3
#define FOLLOW_RATIO_ARROW 0.43
#define GAMEEND_ENEMY_DEATH_COUNT 4
#define PLYER_HIT_CIRCLE_COLOR Color3B(110,110,110)
#define SOUND_BGM_PLAY "sound/Laser_Groove.mp3"
#define SOUND_SE_HIT_PLAYER "sound/NFF-exploding-baloon.wav"
#define SOUND_SE_HIT_ENEMY "sound/NFF-stuff-up.wav"

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

	mVisibleSize = Director::getInstance()->getVisibleSize();

#pragma region Sound
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic(SOUND_BGM_PLAY);
	audio->preloadEffect(SOUND_SE_HIT_PLAYER);
	audio->preloadEffect(SOUND_SE_HIT_ENEMY);
	
#pragma endregion


	//root
	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);

	//root->uiNode
	mUINode = Node::create();
	mRenderNode->addChild(mUINode, 10);

#pragma region UI

	mUIPadBack = Sprite::create("ui/pad/ui_pad_back.jpg");
	mUIPadBack->setAnchorPoint(Vec2(0.5, 0));
	mUIPadBack->setPosition(Vec2(mVisibleSize.width*0.5, 0));
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
	mKillCountBackground->setTextureRect(Rect(0, 0, mVisibleSize.width, mVisibleSize.height*0.11f));
	mKillCountBackground->setAnchorPoint(Vec2(0, 0.5f));
	mKillCountBackground->setColor(Color3B::BLACK);
	mKillCountBackground->setOpacity(255 * 0.5f);
	mKillCountBackground->setPosition(-mKillCountBackground->getContentSize().width, mVisibleSize.height*0.85f);

	mKillCountLabel = Label::createWithTTF("99", "fonts/NotoSansKR-Regular-Hestia.otf", 85);
	mKillCountLabel->setColor(Color3B::WHITE);
	mKillCountLabel->setPosition(
		mKillCountBackground->getContentSize().width*0.5f,
		mKillCountBackground->getContentSize().height*0.5f);
	mKillCountBackground->addChild(mKillCountLabel);
	


	mUINode->addChild(mKillCountBackground);

#pragma endregion

	mFadeSprite = Sprite::create("white4x4.jpg");
	mFadeSprite->setTextureRect(Rect(0, 0, mVisibleSize.width, mVisibleSize.height));
	mFadeSprite->setAnchorPoint(Vec2(0, 0));
	mFadeSprite->setColor(Color3B::BLACK);
	this->addChild(mFadeSprite, 10);

	//root->playNode
	mPlayNodeSize = Size(mVisibleSize.width, mVisibleSize.height - uiPadBackSize.height);
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

	mPlayerHitCircle = new SWDrawCircle();
	mPlayerHitCircle->GetSprite()->setColor(PLYER_HIT_CIRCLE_COLOR);
	mPlayNode->addChild(mPlayerHitCircle->GetSprite(), ZORDER_PLAYER + 2);
	mPlayerHitCircle->SetCircleSize(0);
	mPlayerHitCircle->SetInline(1);

	mRollCircle = new SWDrawCircle();
	mRollCircle->GetSprite()->setColor(Color3B::WHITE);
	mRollCircle->GetSprite()->setOpacity(255 * 0.75f);
	mPlayNode->addChild(mRollCircle->GetSprite(), ZORDER_PLAYER + 1);
	mRollCircle->SetCircleSize(0);
	mRollCircle->SetInline(1);

	mEFEnemyKill = EffectEnemyKill::create();
	mPlayNode->addChild(mEFEnemyKill, ZORDER_ENEMY + 1);
		
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
			mCurrentEnemy->SetOpacity(1);
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
		mPlayer->GetSprite()->setOpacity(255);

		mArrow->LockOn(Vec2(0, 1), true);

		CalculatePlayNodePosition(1);
	}),
		FadeOut::create(0.15),
		CallFunc::create([this]()
	{
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

	SimpleAudioEngine::getInstance()->playBackgroundMusic(SOUND_BGM_PLAY);
}

void ScenePlay::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);
	CC_SAFE_RELEASE_NULL(mUIPadFrontImage);
	CC_SAFE_DELETE(mPlayerHitCircle);
	CC_SAFE_DELETE(mRollCircle);

	ActorManager::GetInstance()->OnReferenceReset();


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
	else
	{
		mRollCircle->GetSprite()->setPosition(mPlayer->getPosition());
	}

	mArrow->OnCollisionOther(false, nullptr);
}

void ScenePlay::GameOverSequence()
{
	mIsPlaying = false;
	mPlayer->SetIsControl(false);
	
	SimpleAudioEngine::getInstance()->playEffect(SOUND_SE_HIT_PLAYER);

	mPlayerHitCircle->GetSprite()->setPosition(mPlayer->getPosition());

	auto gameOverSeq = Sequence::create(
		Spawn::create(CreateCameraShake(), CreateHitCircle(), nullptr),
		DelayTime::create(0.6f),
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

	mIsPlaying = false;
	mKillCount++;

	SimpleAudioEngine::getInstance()->playEffect(SOUND_SE_HIT_ENEMY);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	auto lastSeq = Spawn::create(
		mEFEnemyKill->CreateAction(mPlayer->getPosition(), mCurrentEnemy->getPosition()),
		CreateCameraShake(),
		ActionFloat::create(1.0f, 1, 0, [this](float value) 
	{
		mCurrentEnemy->SetOpacity(value);
	}),
		nullptr
		);

	Sequence * clearSeq = nullptr;

	if (DataManager::GetInstance()->GetMapData(mCurrentRoomIndex))
	{
		/*if (mCurrentEnemy->GetDeathCount() < GAMEEND_ENEMY_DEATH_COUNT)
		{
			clearSeq = Sequence::create(
				lastSeq,
				CallFunc::create([this]() 
			{
				ShowKillCount();
				this->RoomSequence(mCurrentRoomIndex, true);
			}),
				nullptr);
			mFadeSprite->runAction(clearSeq);
		}
		else
		{
			ShowGameResult();
			mPlayNode->runAction(lastSeq);
		}*/
		ShowGameResult();
		mPlayNode->runAction(lastSeq);
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

FiniteTimeAction * ScenePlay::CreateCameraShake()
{
	auto shake = ActionFloat::create(0.2f, 0, 1, [this](float value)
	{
		float shake = sin(value*10.0f) * powf(0.5f, value);
		Vec2 pos = mPlayNode->getPosition();
		pos.x += 6 * shake;
		pos.y += 6 * shake;
		mPlayNode->setPosition(pos);
	});
	return shake;
}

FiniteTimeAction * ScenePlay::CreateHitCircle()
{
	auto hitCircle = Spawn::create(
		CallFunc::create([this]() 
	{ 
		mPlayer->GetSprite()->setOpacity(0);
	}),
		EaseExponentialOut::create(
			ActionFloat::create(0.6f, 0, 1, CC_CALLBACK_1(SWDrawCircle::SetCircleSize, mPlayerHitCircle))),
		Sequence::create(
			EaseQuarticActionIn::create(
				ActionFloat::create(0.4f, 1, 0, CC_CALLBACK_1(SWDrawCircle::SetInline, mPlayerHitCircle))),
			nullptr),
		CallFunc::create([this]()
	{
		mPlayerHitCircle->SetInline(1);
		mPlayerHitCircle->SetCircleSize(0);
	}),
		nullptr);
	return hitCircle;
}

FiniteTimeAction * ScenePlay::CreateRollCircle()
{
	auto action = Sequence::create(
		CallFunc::create([this]() 
	{ 
		mRollCircle->SetInline(0.05f); 
	}),
		EaseExponentialOut::create(
			ActionFloat::create(mPlayer->GetRollDuration() * 0.3f, 0, 0.25f, CC_CALLBACK_1(SWDrawCircle::SetCircleSize, mRollCircle))),
		Spawn::create(
			EaseExponentialOut::create(
				ActionFloat::create(mPlayer->GetRollDuration() * 0.5f, 0.05f, 1.0f, CC_CALLBACK_1(SWDrawCircle::SetInline, mRollCircle))),
			EaseExponentialOut::create(
				ActionFloat::create(mPlayer->GetRollDuration() / 0.5f, 0.25f, 0.0f, CC_CALLBACK_1(SWDrawCircle::SetCircleSize, mRollCircle))),
			nullptr),
		nullptr);
	return action;
}

void ScenePlay::ShowKillCount()
{
	mKillCountLabel->setString(StringUtils::format("%d", mKillCount));
	mKillCountBackground->runAction(
		Sequence::create(
			EaseExponentialInOut::create(MoveTo::create(0.7, Vec2(0, mKillCountBackground->getPosition().y))),
			DelayTime::create(1),
			EaseExponentialInOut::create(MoveTo::create(0.7, Vec2(-mKillCountBackground->getContentSize().width, mKillCountBackground->getPosition().y))),
			//EaseQuinticActionOut::create(RotateBy::create(1.8, Vec3(360*4,0,0))),
			nullptr));
}

void ScenePlay::ShowGameResult()
{
	//mKillCountLabel->setString(StringUtils::format("%d", mKillCount));
	mKillCountLabel->setString("\n");
	mKillCountBackground->runAction(
		Sequence::create(
			EaseExponentialInOut::create(MoveTo::create(0.7f, Vec2(0, mKillCountBackground->getPosition().y))),
			//DelayTime::create(1),
			RotateTo::create(0.15f,Vec3(110,0,0)),
			CallFunc::create([this]() 
			{	
				mKillCountBackground->setTextureRect(Rect(0, 0, mVisibleSize.width, mVisibleSize.height * 0.35f));
				mKillCountLabel->setString("CLEAR");
				mKillCountLabel->setScale(1.7);
				mKillCountLabel->getFontAtlas()->getTexture(0)->setAliasTexParameters();
				mKillCountLabel->setPositionY(mKillCountBackground->getContentSize().height * 0.5f);

			}),
			Spawn::create(
				MoveTo::create(0,Vec2(0, mVisibleSize.height * 0.72f)),
				EaseQuinticActionOut::create(RotateTo::create(0.3f, Vec3(0, 0, 0))),
				nullptr),
			DelayTime::create(0.6f),
			Spawn::create(
				EaseExponentialInOut::create(MoveBy::create(0.6, Vec2(-mKillCountBackground->getContentSize().width, 0))),
				CallFunc::create([]() 
				{
					//Director::getInstance()->popScene();

					Director::getInstance()->replaceScene(TransitionFade::create(1, SceneTitle::createScene()));
				}),
				nullptr),
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
			|| !(mUIPadFront->getBoundingBox().containsPoint(touchPos)
			&& CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
		{
			Vec2 dir = touch->getLocation() - mTouchBeganPos;
			float endedRadian = atan2(dir.y, dir.x);

			if (mPlayer->OnRoll(endedRadian))
			{
				this->runAction(CreateRollCircle());
			}
		}
		mArrow->DisableLockOn();
		mUIPadFront->setColor(Color3B::WHITE);
		break;
	case TouchState::Collect:
		mArrow->SetReturnArrow(false);
		mCameraSecondTarget = mCurrentEnemy;

		//camera follow
		mShakeStopWatch->OnStop();

		mCameraSecondTarget = mCurrentEnemy;
		mFollowRatio = FOLLOW_RATIO_ENEMY;
		
		break;
	}


	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

}

