#include "CBullet.h"
#include "CEnemy.h"
#include "CActor.h"

bool CBullet::init()
{
	if (!CUnit::init())
	{
		return false;
	}

	mSprite = Sprite::create("bullet.png");
	mSprite->setScale(0.5f);
	//mSprite->setVisible(false);
	this->addChild(mSprite);

	setIsAlive(false);
	this->scheduleUpdate();
	return true;
}


void CBullet::update(float dt)
{
	if (mIsAlive)
	{
		bulletUpdate(dt);

		if (isScreenOut(this->getPosition()))
		{
			setIsAlive(false);
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

bool CBullet::isScreenOut(Vec2 tPos)
{
	/*Rect tScreen = Rect(0, 0,
		Director::getInstance()->getVisibleSize().width,
		Director::getInstance()->getVisibleSize().height *  1.5);

	if (tScreen.containsPoint(tPos) == false)
	{
		return true;
	}*/
	if (tPos.x < 0 || tPos.x > Director::getInstance()->getVisibleSize().width ||
		tPos.y < -100 || tPos.y > Director::getInstance()->getVisibleSize().height + 100)
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

void CBullet::setColor(const Color3B & tColor)
{
	this->mSprite->setColor(tColor);
}

Sprite * CBullet::getSprite() const
{
	return mSprite;
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

void CBullet::shot(Vec2 tPos)
{
	this->setPosition(tPos);
	setIsAlive(true);
	mShotPos = tPos;
}

void CBullet::checkCollisionEnemy(CEnemy * enemy)
{
	if (mIsAlive)
	{
		if (enemy->checkCollisionBulletToParts(this))
		{
			this->setIsAlive(false);
		}
	}
}

void CBullet::checkCollisionActor(CActor * actor)
{
	if (mIsAlive)
	{
		if (utils::getCascadeBoundingBox(this).intersectsCircle(
			actor->getPosition(), actor->getRedius()
		))
		{
			actor->hit();
			this->setIsAlive(false);
		}
	}
}



