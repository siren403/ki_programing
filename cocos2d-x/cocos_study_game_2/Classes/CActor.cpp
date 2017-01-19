#include "CActor.h"
#include "SpriteAnimator.h"
#include "BulletFactory.h"

#define USE_MOUSE_POSITION true
#define BULLET_MAX_COUNT 30
#define BULLET_INTERVAL 0.1
#define BULLET_SPEED 600

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

	mSpriteAnim = SpriteAnimator::create("actor", 0, 20, 0.1);
	mSpriteAnim->runAni();
	this->addChild(mSpriteAnim);

	mBulletInterval = BULLET_INTERVAL;
	mBullets.reserve(BULLET_MAX_COUNT);

	CBullet * tTempPattern = nullptr;
	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		
		tTempPattern = BulletFactory::creataBullet3Way(
			DirSpeed(Vec2(1, 0), BULLET_SPEED),
			DirSpeed(Vec2(1, -0.3), BULLET_SPEED),
			DirSpeed(Vec2(1, 0.3), BULLET_SPEED));

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
	tTouchListener->onTouchMoved = CC_CALLBACK_2(CActorW::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouchListener, this);

#endif
	this->scheduleUpdate();
	return true;
}


void CActor::update(float dt)
{
	if (mIsControl)
	{
		mLatestShotTime += dt;
		if (mLatestShotTime >= mBulletInterval)
		{
			if (mBullets.at(mCurrentBulletIndex)->getIsAlive() == false)
			{
				Vec2 tPos = this->getPosition();
				tPos.x += mSpriteAnim->getContentSize().width;
				tPos.y += mSpriteAnim->getContentSize().height * 0.5;

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
}

void CActor::setIsControl(bool tIsControl)
{
	mIsControl = tIsControl;
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

