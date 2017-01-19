#include "CActor.h"
#include "CBulletDirection.h"
#include "CBulletPattern.h"

#define USE_MOUSE_POSITION true
#define BULLET_MAX_COUNT 30
#define BULLET_INTERVAL 0.1

CActor * CActor::create(Layer * tBulletLayer)
{
	auto actor = CActor::create();
	if (actor != nullptr)
	{
		actor->mBulletLayer = tBulletLayer;
		actor->lateInit();
	}
	return actor;
}

bool CActor::lateInit()
{
	if (!CUnit::lateInit())
	{
		return false;
	}

	mSprite = Sprite::create("actor.png");
	mSprite->setRotation(90);
	this->addChild(mSprite);


	mBulletInterval = BULLET_INTERVAL;
	mBullets.reserve(BULLET_MAX_COUNT);

	CBulletDirection * tTempBullet = nullptr;
	/*
	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		tTempBullet = CBulletDirection::create(Sprite::create("bullet.png"));
		tTempBullet->setDirection(Vec2(0, 1));
		tTempBullet->setSpeed(400);
		mBullets.pushBack(tTempBullet);
		mBulletLayer->addChild(tTempBullet);
	}*/

	int tBulletSpeed = 600;
	CBulletPattern * tTempPattern = nullptr;
	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		tTempPattern = CBulletPattern::create();
		tTempPattern->bulletReserve(3);

		tTempBullet = CBulletDirection::create(Sprite::create("bullet.png"));
		tTempBullet->setDirection(Vec2(1, 0));
		tTempBullet->setSpeed(tBulletSpeed);
		tTempPattern->pushBullet(tTempBullet);

		tTempBullet = CBulletDirection::create(Sprite::create("bullet.png"));
		tTempBullet->setDirection(Vec2(1, -0.3));
		tTempBullet->setSpeed(tBulletSpeed);
		tTempPattern->pushBullet(tTempBullet);

		tTempBullet = CBulletDirection::create(Sprite::create("bullet.png"));
		tTempBullet->setDirection(Vec2(1, 0.3));
		tTempBullet->setSpeed(tBulletSpeed);
		tTempPattern->pushBullet(tTempBullet);

		mBullets.pushBack(tTempPattern);
		mBulletLayer->addChild(tTempPattern);
	}


#if USE_MOUSE_POSITION

	auto tMouseListener = EventListenerMouse::create();
	tMouseListener->onMouseMove = [=](Event * event) 
	{
		auto tMouse = (EventMouse *)event;
		//this->setPosition(tMouse->getLocationInView());
		mLatestInputPos = tMouse->getLocationInView();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tMouseListener, this);

#else

	auto tTouchListener = EventListenerTouchOneByOne::create();
	tTouchListener->setSwallowTouches(true);
	tTouchListener->onTouchBegan = CC_CALLBACK_2(CActor::onTouchBegan, this);
	tTouchListener->onTouchMoved = CC_CALLBACK_2(CActor::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouchListener, this);

#endif
	this->scheduleUpdate();
	return true;
}


void CActor::update(float dt)
{
	mLatestShotTime += dt;
	if (mLatestShotTime >= mBulletInterval)
	{
		if (mBullets.at(mCurrentBulletIndex)->getIsAlive() == false)
		{
			Vec2 tPos = this->getPosition();
			tPos.x += mSprite->getContentSize().height;
			mBullets.at(mCurrentBulletIndex)->Shot(tPos);
			mCurrentBulletIndex++;
			if (mCurrentBulletIndex >= mBullets.size())
			{
				mCurrentBulletIndex = 0;
			}
		}
		mLatestShotTime = 0;
	}

	Vec2 tPos = this->getPosition();
	tPos = ccpLerp(tPos, mLatestInputPos, dt * mFollowSpeed);
	this->setPosition(tPos);
}

CActor::~CActor()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}


bool CActor::onTouchBegan(Touch * touch, Event * unused_event)
{
	this->setPosition(touch->getLocation());
	return true;
}

void CActor::onTouchMoved(Touch * touch, Event * unused_event)
{
	this->setPosition(touch->getLocation());
}

