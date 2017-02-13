#include "ScenePlay.h"
#include "CollisionUtils.h"
#include "StopWatch.h"
#include "Boss.h"
#include "ActorManager.h"
#include "PlayMap.h"
#include "MapTile.h"


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

	mTouchSlideTime = 0.25;
	mTouchStopWatch = StopWatch::create();
	this->addChild(mTouchStopWatch);


	//root->playNode
	mPlayNodeSize = Size(visibleSize.width, visibleSize.height - uiPadBackSize.height);
	mPlayNode = Node::create();
	mPlayNode->setPosition(Vec2(0, uiPadBackSize.height));

	mRenderNode->addChild(mPlayNode, 0);

#pragma region Map 
	
	mPlayMap = PlayMap::create();
	mPlayMap->CreateTiles(0);
	mPlayMap->setScale(2 * CC_CONTENT_SCALE_FACTOR());
	mPlayNode->addChild(mPlayMap, 0);

	Size mapContentSize = mPlayMap->GetMapContentSize();
#pragma endregion

#pragma region Player

	mPlayer = Player::create();
	mPlayer->setPosition(mapContentSize.width*0.5, mapContentSize.height*0.2);
	//mPlayer->setPosition(mapContentSize.width*0.0, mapContentSize.height*0.0);

	mPlayer->SetIsControl(true);
	mPlayer->SetMoveArea(mapContentSize);
	mPlayNode->addChild(mPlayer, 1);

	mArrow = Arrow::create();
	mArrow->InitWithPlayer(mPlayer);
	mPlayNode->addChild(mArrow, mPlayer->getLocalZOrder() + 1);

	ActorManager::GetInstance()->SetPlayer(mPlayer);


#pragma endregion

#pragma region Enemy

	mCurrentEnemy = Boss::create();
	mCurrentEnemy->setPosition(mapContentSize.width * 0.5, mapContentSize.height * 0.55);
	mPlayNode->addChild(mCurrentEnemy, 5);

#pragma endregion


	//auto Spr = Sprite::create("CloseNormal.png");
	//Spr->setScale(0.5);
	//Spr->setPosition(360,905);
	//Spr->setGlobalZOrder(10);
	//this->addChild(Spr);

	this->scheduleUpdate();
	return true;
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
#pragma region Arrow Collision

	if (mCurrentEnemy != nullptr)
	{
		mCurrentEnemy->CheckCollisionActor(mArrow);
	}
	mPlayMap->CheckCollisionTile(mArrow, mArrow->GetMoveDirection());

#pragma endregion
#pragma region Player Collision

	mCurrentEnemy->CheckCollisionActor(mPlayer);
	mPlayMap->CheckCollisionTile(mPlayer, mPlayer->GetMoveDir());

#pragma endregion

#pragma region Check Tile Search
	auto tile = mPlayMap->GetTile(mPlayer->getPosition());
	if (tile->GetSprite()->getColor() != Color3B::RED)
	{
		tile->GetSprite()->setColor(Color3B::RED);
	}

	tile = mPlayMap->GetTile(mArrow->getPosition());
	if (tile->GetSprite()->getColor() != Color3B::GREEN)
	{
		tile->GetSprite()->setColor(Color3B::GREEN);
	}
#pragma endregion


#pragma region Map Scroll

	Vec2 pos = mPlayer->getPosition();
	//log("%f,%f", pos.x, pos.y);

	pos.x = mPlayNodeSize.width * 0.5;
	pos.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;
	//log("%f,%f", pos.x, pos.y);

	Vec2 origin;
	origin.x = mPlayNodeSize.width * 0.5;
	origin.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;

	pos = origin - mPlayer->getPosition();

	//log("%f,%f", pos.y, mUIPadBack->getContentSize().height);
	pos.y = MIN(pos.y, mUIPadBack->getContentSize().height);
	mPlayNode->setPosition(pos);

#pragma endregion


}

bool ScenePlay::onTouchBegan(Touch * touch, Event * unused_event)
{
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
			mTouchStopWatch->OnStart();
			isTouchMoved = true;
		}
		else if(mArrow->GetState() != Arrow::State::State_Drop)//attack
		{
			mTouchBeganPos = touch->getLocation();
			mTouchState = TouchState::Shot;

			Vec2 dir = mTouchBeganPos - convertToWorldSpace(mUIPadFront->getPosition());
			mArrow->LockOn(dir.getNormalized());
			isTouchMoved = true;
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

		break;
	}
}

void ScenePlay::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());

	switch (mTouchState)
	{
	case TouchState::Shot:
		mArrow->Shot();
		break;
	case TouchState::Move:
		if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
		{
			if (!(mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
				CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
			{
				Vec2 dir = touch->getLocation() - mTouchBeganPos;
				float endedRadian = atan2(dir.y, dir.x);
				mPlayer->OnRoll(endedRadian);
			}
		}
		mArrow->DisableLockOn();
		break;
	case TouchState::Collect:
		mArrow->SetReturnArrow(false);
		break;
	}


	/*float touchTime = mTouchStopWatch->OnStop();

	if (touchTime > mTouchSlideTime)
	{
		mPlayer->SetMoveDir(Vec2::ZERO);
	}
	else
	{
		Vec2 pos = touch->getLocation() - mTouchBeganPos;
		float endedRadian = atan2(pos.y, pos.x);
		mPlayer->OnRoll(endedRadian);
	}*/

	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

}

int ScenePlay::ClampI(int value, int min, int max)
{
	return value < min ? min : value>max ? max : value;
}