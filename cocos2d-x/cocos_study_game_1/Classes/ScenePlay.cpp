#include "ScenePlay.h"
#include "Mole.h"
#include <stdlib.h>
#include <time.h>

#define MOLE_SCORE 1450
#define LIMIT_TIME 5

Scene * ScenePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = ScenePlay::create();

	scene->addChild(layer);

	return scene;
}

bool ScenePlay::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	srand(time(nullptr));

	auto tVisibleSize = Director::getInstance()->getVisibleSize();

#pragma region UI


	auto tUILayer = Layer::create();
	this->addChild(tUILayer, 10);

	mLabelScore = Label::create("Score", "fonts/arial.ttf", 20);
	mLabelScore->setColor(Color3B::BLACK);
	mLabelScore->setAnchorPoint(Vec2(1, 1));
	mLabelScore->setPosition(Vec2(tVisibleSize.width*0.98f, tVisibleSize.height*0.98f));
	tUILayer->addChild(mLabelScore, 0);

	mSpriteTime = Sprite::create("white-512x512.png");
	mSpriteTime->setColor(Color3B::RED);
	mSpriteTime->setTextureRect(Rect(0, 0, 300, 20));
	mSpriteTime->setAnchorPoint(Vec2(0, 0.5));
	mSpriteTime->setPosition(Vec2((tVisibleSize.width*0.5)- 150, tVisibleSize.height*0.9));
	tUILayer->addChild(mSpriteTime, 1);

#pragma endregion

	auto tSpriteUpper = Sprite::create("grass_upper.png");
	tSpriteUpper->setAnchorPoint(Vec2(0, 1));
	tSpriteUpper->setPosition(Vec2(0, tVisibleSize.height));
	this->addChild(tSpriteUpper, 1);


	auto tSpriteLower = Sprite::create("grass_lower.png");
	tSpriteLower->setAnchorPoint(Vec2(0, 0));
	tSpriteLower->setPosition(Vec2(0, 0));
	this->addChild(tSpriteLower, 3);

	float tMoleLineY = tVisibleSize.height*0.55f;

	auto Mole_1 = Mole::create();
	Mole_1->setAnchorPoint(Vec2(0.5, 0));
	Mole_1->setPosition(Vec2(tVisibleSize.width*0.2f, tMoleLineY));
	this->addChild(Mole_1, 2);

	auto Mole_2 = Mole::create();
	Mole_2->setAnchorPoint(Vec2(0.5, 0));
	Mole_2->setPosition(Vec2(tVisibleSize.width*0.5f, tMoleLineY));
	this->addChild(Mole_2, 2);

	auto Mole_3 = Mole::create();
	Mole_3->setAnchorPoint(Vec2(0.5, 0));
	Mole_3->setPosition(Vec2(tVisibleSize.width*0.8f, tMoleLineY));
	this->addChild(Mole_3, 2);

	mMoles.reserve(3);
	mMoles.push_back(Mole_1);
	mMoles.push_back(Mole_2);
	mMoles.push_back(Mole_3);

	auto tStartSeq = Sequence::create(
		DelayTime::create(1),
		CallFunc::create([&]() 
	{
		for (int i = 0; i < mMoles.size(); i++)
		{
			mMoles[i]->start();
		}
		mLabelScore->setString(StringUtils::toString(mCurrentScore));
		mCurrentTime = 0;
		mIsUpdate = true;
	}),
		nullptr
	);

	this->runAction(tStartSeq);

	return true;
}

void ScenePlay::update(float dt)
{
	if (mIsUpdate)
	{
		mCurrentTime += dt;
		mSpriteTime->setScale((LIMIT_TIME - mCurrentTime) / LIMIT_TIME, 1);
		if (mCurrentTime >= LIMIT_TIME)
		{
			mIsUpdate = false;
			GameEnd();
			log("game end");
		}
	}
}

void ScenePlay::onEnter()
{
	LayerColor::onEnter();

	auto tTouch = EventListenerTouchOneByOne::create();
	tTouch->setSwallowTouches(true);
	tTouch->onTouchBegan = CC_CALLBACK_2(ScenePlay::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouch,this);

	this->scheduleUpdate();
}

void ScenePlay::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);
	this->unscheduleUpdate();

	LayerColor::onExit();
}

bool ScenePlay::onTouchBegan(Touch * touch, Event * event)
{
	for (int i = 0; i < mMoles.size(); i++)
	{
		if (mMoles[i]->checkHit(touch->getLocation()))
		{
			log("hit");
			mCurrentScore += MOLE_SCORE;
			mLabelScore->setString(StringUtils::toString(mCurrentScore));
			break;
		}
	}
	
	return true;
}

void ScenePlay::GameEnd()
{
	for (int i = 0; i < mMoles.size(); i++)
	{
		mMoles[i]->stop();
	}
}
