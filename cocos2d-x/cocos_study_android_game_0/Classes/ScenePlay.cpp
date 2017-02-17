#include "ScenePlay.h"

#include "Player.h"
#include "CollisionUtils.h"
#include "Boss.h"
#include "ActorManager.h"
#include "PlayMap.h"
#include "MapTile.h"
#include "DataManager.h"

#define ZORDER_ENEMY 5
#define IS_IMMOTAL_PLAYER true

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

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//root
	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);


	//root->uiNode
	mUINode = Node::create();
	mRenderNode->addChild(mUINode, 10);

#pragma region Pad

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

	mPlayNodeOffsetScalar = 300;
	mPlayNodeOffsetDirection = Vec2::ZERO;

#pragma region Create
	mPlayMap = PlayMap::create();
	mPlayNode->addChild(mPlayMap, 0);

	mPlayer = ActorManager::GetInstance()->GetPlayer();
	mPlayNode->addChild(mPlayer, 1);

	mArrow = Arrow::create();
	mArrow->InitWithPlayer(mPlayer);
	mPlayNode->addChild(mArrow, mPlayer->getLocalZOrder() + 1);
#pragma endregion
	
	RoomSequence(0);

	/*auto tSeq = Sequence::create(
		DelayTime::create(10),
		CallFunc::create([this]() 
	{
		RoomSequence(mCurrentRoomIndex + 1);
	}),
		nullptr
	);
	this->runAction(tSeq);*/

	//auto Spr = Sprite::create("CloseNormal.png");
	//Spr->setScale(0.5);
	//Spr->setPosition(360,905);
	//Spr->setGlobalZOrder(10);
	//this->addChild(Spr);

	this->scheduleUpdate();
	return true;
}


void ScenePlay::RoomSequence(int roomIndex, bool isReset)
{
	mCurrentRoomIndex = roomIndex;
	mIsPlaying = false;
	mPlayer->SetIsControl(false);
	mPlayer->SetAlive(true);

	auto mapData = DataManager::GetInstance()->GetMapData(roomIndex);
	if (mapData == nullptr)
	{
		log("nothing map");
		Director::getInstance()->end();
		return;
	}

	auto tSeq = Sequence::create(
		FadeIn::create(1),
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
				mCurrentEnemy = ActorManager::GetInstance()->GetEnemy(stageData->enemy.id);
				mPlayNode->addChild(mCurrentEnemy, ZORDER_ENEMY);
			}

			Vec2 pos;
			pos.x = mPlayMap->GetMapContentSize().width * stageData->enemy.position.x;
			pos.y = mPlayMap->GetMapContentSize().height * stageData->enemy.position.y;
			mCurrentEnemy->setPosition(pos);
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


		Vec2 initPos;
		initPos.x = mPlayMap->GetMapContentSize().width * 0.5;
		initPos.y = mPlayMap->GetMapContentSize().height * 0.1;
		mPlayer->InitPosition(initPos);

		//mPlayer->SetMoveArea(mapContentSize);

		mArrow->LockOn(Vec2(0, 1), true);

		CalculatePlayNodePosition(1);
	}),
		DelayTime::create(0.1),
		FadeOut::create(1),
		CallFunc::create([this]()
	{
		mPlayer->SetIsControl(true);
		if (mCurrentEnemy != nullptr)
		{
			mCurrentEnemy->OnActivate(true);
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
	CalculatePlayNodePosition(dt * 2);

#pragma region Tile Collision

	mPlayMap->CheckCollisionTile(mArrow, mArrow->GetMoveDirection());
	mPlayMap->CheckCollisionTile(mPlayer, mPlayer->GetMoveDir());

#pragma endregion

#pragma region Check Tile Search
	auto tile = mPlayMap->GetTile(mPlayer->getPosition());
	if (tile->GetSprite()->getColor() != Color3B::RED)
	{
		//tile->GetSprite()->setColor(Color3B::RED);
	}

	tile = mPlayMap->GetTile(mArrow->getPosition());
	if (tile->GetSprite()->getColor() != Color3B::GREEN)
	{
		//tile->GetSprite()->setColor(Color3B::GREEN);
	}
#pragma endregion

	//Map Scroll

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
		if (IS_IMMOTAL_PLAYER == false)
		{
			mCurrentEnemy->CheckCollisionActor(mPlayer);
		}
		if (mCurrentEnemy->IsAlive() == false)
		{
			log("clear");
			RoomClearSequence();
			return;
		}
	}
#pragma endregion
	if (mPlayer->IsAlive() == false)
	{
		log("gameover");
		GameOverSequence();
		return;
	}

	mArrow->OnCollisionOther(false, nullptr);
}

void ScenePlay::GameOverSequence()
{
	mIsPlaying = false;
	mPlayer->SetIsControl(false);
	mCurrentEnemy->OnActivate(false);

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
	mCurrentEnemy->OnActivate(false);

	auto gameOverSeq = Sequence::create(
		CallFunc::create([]()
	{
		Director::getInstance()->getScheduler()->setTimeScale(0.2);
	}),
		DelayTime::create(0.3),
		CallFunc::create([]()
	{
		Director::getInstance()->getScheduler()->setTimeScale(1);
	}),
		CallFunc::create([this]()
	{
		this->RoomSequence(mCurrentRoomIndex + 1);
	}),
		nullptr
		);

	mPlayNode->runAction(gameOverSeq);
}

void ScenePlay::CalculatePlayNodePosition(float dt)
{
	Vec2 pos;// = mPlayer->getPosition();
			 //log("%f,%f", pos.x, pos.y);

			 /*pos.x = mPlayNodeSize.width * 0.5;
			 pos.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;*/
			 //log("%f,%f", pos.x, pos.y);

	Vec2 origin;
	origin.x = mPlayNodeSize.width * 0.5;
	origin.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;

	pos = (origin - mPlayer->getPosition()) + Vec2(-mPlayNodeOffsetDirection.x * mPlayNodeOffsetScalar, -mPlayNodeOffsetDirection.y * mPlayNodeOffsetScalar);

	//log("%f,%f", pos.y, mUIPadBack->getContentSize().height);
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
			//mTouchBeganPos = touch->getLocation();
			mTouchBeganPos = convertToWorldSpace(mUIPadFront->getPosition());
			mTouchState = TouchState::Move;
			isTouchMoved = true;
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

		//log("%f,%f", dir.x, dir.y);

		dir.x = clampf(dir.x / 60, -1, 1);
		dir.y = clampf(dir.y / 60, -1, 1);

		mPlayer->SetMoveDir(dir);

		//mArrow->LockOn(atan2(dir.y, dir.x));
		mArrow->LockOn(dir.getNormalized());

		//log("%f", atan2(dir.y, dir.x));
		break;
	case TouchState::Shot:
		dir = mTouchBeganPos - touchPos;
		//mArrow->LockOn(atan2(dir.y, dir.x));
		mArrow->LockOn(dir.getNormalized());

		mPlayNodeOffsetDirection = dir.getNormalized();
		break;
	}
}

void ScenePlay::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());

	switch (mTouchState)
	{
	case TouchState::Shot:
		if (mTouchBeganPos.distance(touchPos) > 5)
		{
			mArrow->Shot();
		}
		mPlayNodeOffsetDirection = Vec2::ZERO;
		break;
	case TouchState::Move:
		//if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
		//{
		if (!(mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
			CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
		{
			Vec2 dir = touch->getLocation() - mTouchBeganPos;
			float endedRadian = atan2(dir.y, dir.x);
			mPlayer->OnRoll(endedRadian);
		}
		//}
		mArrow->DisableLockOn();
		break;
	case TouchState::Collect:
		mArrow->SetReturnArrow(false);
		break;
	}


	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

}

