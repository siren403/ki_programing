#include "ScenePlay.h"
#include "CollisionUtils.h"
#include "StopWatch.h"

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

#pragma region Layers
	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);
#pragma endregion

	mUINode = Node::create();
	mRenderNode->addChild(mUINode, 10);

#pragma region Pad

	mUIPadBack = Sprite::create("ui/pad/ui_pad_back.jpg");
	mUIPadBack->setAnchorPoint(Vec2(0.5, 0));
	mUIPadBack->setPosition(Vec2(visibleSize.width*0.5, 0));
	mUINode->addChild(mUIPadBack, 0);

	mUIPadFrontImage = new Image();
	mUIPadFrontImage->initWithImageFile("ui/pad/ui_pad_front.png");
	mUIPadFrontImage->autorelease();
	mUIPadFrontImage->retain();

	mUIPadFront = Sprite::create("ui/pad/ui_pad_front.png");
	Size uiPadBackSize = mUIPadBack->getContentSize();
	mUIPadFront->setPosition(Vec2(uiPadBackSize.width*0.5, uiPadBackSize.height*0.5));
	mUINode->addChild(mUIPadFront, 1);

	mPadMaxDistance = 3;
#pragma endregion

	mTouchSlideTime = 0.25;
	mTouchStopWatch = StopWatch::create();
	this->addChild(mTouchStopWatch);

#pragma region Player

	mPlayNodeSize = Size(visibleSize.width, visibleSize.height - uiPadBackSize.height);
	mPlayNode = Node::create();
	mPlayNode->setPosition(Vec2(0, uiPadBackSize.height));
	mRenderNode->addChild(mPlayNode, 0);
	

	mPlayer = Player::create();
	mPlayer->setPosition(visibleSize.width*0.25, mPlayNodeSize.height*0.5);
	mPlayNode->addChild(mPlayer, 1);
	mPlayer->SetIsControl(true);
	mPlayer->SetMoveArea(mPlayNodeSize);

#pragma endregion


	

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

}

bool ScenePlay::onTouchBegan(Touch * touch, Event * unused_event)
{
	bool isTouchMoved = false;
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());
	if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
	{
		if (mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
			CollisionUtils::ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos))//move
		{
			mTouchBeganPos = touch->getLocation();
			mTouchState = TouchState::Move;
			isTouchMoved = true;

			mTouchStopWatch->OnStart();
		}
		else//attack
		{
			mTouchState = TouchState::Shot;
			isTouchMoved = true;
		}
	}

	return isTouchMoved;
}

void ScenePlay::onTouchMoved(Touch * touch, Event * unused_event)
{
	Vec2 touchPos = touch->getLocation();
	touchPos.clamp(Vec2::ZERO, mUIPadBack->getContentSize());
	Vec2 dir = touchPos - mTouchBeganPos;

	switch (mTouchState)
	{
	case TouchState::Move:

		//log("%f,%f", dir.x, dir.y);

		dir.x = clampf(dir.x / 60, -1, 1);
		dir.y = clampf(dir.y / 60, -1, 1);

		mPlayer->SetMoveDir(dir);

		break;
	case TouchState::Shot:
		break;
	}
}

void ScenePlay::onTouchEnded(Touch * touch, Event * unused_event)
{
	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());
	if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
	{
		if (!(mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
			CollisionUtils::ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
		{
			Vec2 pos = touch->getLocation() - mTouchBeganPos;
			float endedRadian = atan2(pos.y, pos.x);
			mPlayer->OnRoll(endedRadian);
		}
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
}

