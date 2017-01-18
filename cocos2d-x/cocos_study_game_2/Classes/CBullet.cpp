#include "CBullet.h"


bool CBullet::lateInit()
{
	if (!CUnit::lateInit())
	{
		return false;
	}
	return true;
}


void CBullet::update(float dt)
{
	if (mIsAlive)
	{
		bulletUpdate(dt);

		if (isScreenOut())
		{
			mIsAlive = false;
			this->setVisible(false);
		}
	}
}

void CBullet::bulletUpdate(float dt)
{
}

void CBullet::setSprite(Sprite * tSprite)
{
	if (mSprite != nullptr)
	{
		this->removeChild(mSprite);
	}

	if (tSprite != nullptr)
	{
		mSprite = tSprite;
		this->addChild(mSprite);
	}
}

bool CBullet::isScreenOut()
{
	Rect tScreen = Rect(0, 0, 
		Director::getInstance()->getVisibleSize().width,
		Director::getInstance()->getVisibleSize().height);

	if (tScreen.containsPoint(this->getPosition()) == false)
	{
		return true;
	}

	return false;
}

#pragma region getter,setter

void CBullet::setDirection(Vec2 tDir)
{
	mCurrenDir = tDir;
}

void CBullet::setSpeed(float tSpeed)
{
	mCurrentSpeed = tSpeed;
}

bool CBullet::getIsAlive()
{
	return mIsAlive;
}

void CBullet::setIsAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
	this->setVisible(tIsAlive);
}

#pragma endregion

void CBullet::Shot(Vec2 tPos)
{
	this->setPosition(tPos);
	setIsAlive(true);
}



