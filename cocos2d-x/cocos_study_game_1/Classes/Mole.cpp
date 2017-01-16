#include "Mole.h"

bool Mole::init()
{
	if (!Node::init())
	{
		return false;
	}

	mSprite = Sprite::create("mole.png");
	mSprite->setPosition(Vec2::ZERO);
	mSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mSprite);

	return true;
}

void Mole::start()
{
	if (mIsActive)
	{
		return;
	}
	mLowerPos = Vec2(this->getPosition().x, this->getPosition().y - mMoveY);
	mUpperPos = this->getPosition();

	mIsActive = true;
	mCurrentAction = Sequence::create(
		MoveTo::create(mMoveDuration, mLowerPos),
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(Mole::stateIdle, this)),
		nullptr
	);

	this->runAction(mCurrentAction);
}

void Mole::stop()
{
	if (mIsActive == false)
	{
		return;
	}

	mIsActive = false;
	mIsHitable = false;
	this->stopAction(mCurrentAction);
	this->runAction(MoveTo::create(mMoveDuration, mLowerPos));
}

bool Mole::checkHit(Vec2 touchPos)
{
	if (mIsActive && mIsHitable)
	{
		touchPos = this->convertToNodeSpace(touchPos);
		if (mSprite->getBoundingBox().containsPoint(touchPos))
		{
			this->stopAction(mCurrentAction);
			stateHit();
			return true;
		}
	}
	return false;
}

float Mole::getRandomValue(float max)
{
	return ((float)rand() / RAND_MAX) * max;
}

void Mole::stateIdle()
{
	if (!mIsActive) return;


	mCurrentAction = Sequence::create(
		DelayTime::create(getRandomValue(0.5)),
		MoveTo::create(mMoveDuration, mUpperPos),
		CallFunc::create([this]() { this->mIsHitable = true; }),
		DelayTime::create(getRandomValue(1)),
		CallFunc::create(CC_CALLBACK_0(Mole::stateHide, this)),
		nullptr
	);

	this->runAction(mCurrentAction);
}

void Mole::stateHit()
{
	mIsHitable = false;
	mCurrentAction = Sequence::create(
		ScaleTo::create(0.1f, 1.1),
		ScaleTo::create(0.1f, 1),
		EaseExponentialOut::create(MoveTo::create(0.15, mLowerPos)),
		CallFunc::create(CC_CALLBACK_0(Mole::stateIdle, this)),
		nullptr
	);
	this->runAction(mCurrentAction);
}

void Mole::stateHide()
{
	mIsHitable = false;
	mCurrentAction = Sequence::create(
		MoveTo::create(mMoveDuration, mLowerPos),
		DelayTime::create(getRandomValue(1)),
		CallFunc::create(CC_CALLBACK_0(Mole::stateIdle, this)),
		nullptr
	);

	this->runAction(mCurrentAction);

}


