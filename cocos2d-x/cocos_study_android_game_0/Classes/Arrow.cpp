#include "Arrow.h"
#include "Player.h"

#define PI 3.14159


bool Arrow::init()
{
	if (!Actor::init())
	{
		return false;
	}

	mSprite = Sprite::create("samples/arrow.png");
	//frontBG->getTexture()->setAliasTexParameters();
	this->addChild(mSprite);

	mState = State::State_Idle;

	this->scheduleUpdate();
	return true;
}

void Arrow::update(float dt)
{
	switch (mState)
	{
	case State::State_Shot:
		updateShot(dt);
		break;
	case State::State_Idle:
	case State::State_LockOn:
		updateLock(dt);
		break;
	}
	
}

void Arrow::InitWithPlayer(Player * player)
{
	mPlayer = player;
}

void Arrow::LockOn(float radian)
{
	if (mState == State::State_Idle || mState == State::State_LockOn)
	{
		mShotRadian = radian;
	}
}

void Arrow::DisableLockOn()
{
	if (mState == State::State_LockOn)
	{
		mState = State::State_Idle;
	}
}


void Arrow::Shot()
{
	if (mState == State::State_Idle || mState == State::State_LockOn)
	{
		mState = State::State_Shot;
		mCurrentSpped = mMaxSpeed;
		Vec2 dir;
		dir.x = cos(mShotRadian);
		dir.y = sin(mShotRadian);
		log("%f,%f,%f", mShotRadian,dir.x, dir.y);
	}
}

void Arrow::updateLock(float dt)
{
	Vec2 arrowPos;
	//mShotRadian += dt;
	//if (mShotRadian >= 2)
	//mShotRadian = 0;

	arrowPos.x = mPlayer->getPosition().x + cos(/*PI **/ mShotRadian) * mPlayer->GetSprite()->getContentSize().width;
	arrowPos.y = mPlayer->getPosition().y + sin(/*PI **/ mShotRadian) * mPlayer->GetSprite()->getContentSize().width;

	this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + /*PI **/ mShotRadian));
	this->setPosition(arrowPos);
}

void Arrow::updateShot(float dt)
{
	/*static float time = 0;
	time += dt;
	if (time >= 1)
	{
		time = 0;
		mState = State::State_Drop;
	}*/

	
	//pos.x = 
}






