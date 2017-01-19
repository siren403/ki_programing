#include "CBulletPattern.h"
#include "CEnemy.h"
#include "CActor.h"

void CBulletPattern::pushBullet(CBullet * tBullet)
{
	mBullets.pushBack(tBullet);
	this->addChild(tBullet);
}

void CBulletPattern::bulletReserve(int size)
{
	mBullets.reserve(size);
}


bool CBulletPattern::getIsAlive()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		if (mBullets.at(i)->getIsAlive())
		{
			return true;
		}
	}
	return false;
}

void CBulletPattern::setIsAlive(bool tIsAlive)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets.at(i)->setIsAlive(tIsAlive);
	}
}

void CBulletPattern::shot(Vec2 tPos)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets.at(i)->shot(tPos);
		mBullets.at(i)->setIsAlive(true);
	}
}

void CBulletPattern::setColor(const Color3B & tColor)
{
	if (mBullets.size() > 0)
	{
		for (int i = 0; i < mBullets.size(); i++)
		{
			mBullets.at(i)->setColor(tColor);
		}
	}
}

void CBulletPattern::checkCollisionEnemy(CEnemy * enemy)
{
	if (mBullets.size() > 0)
	{
		CBullet * tBullet = nullptr;
		for (int i = 0; i < mBullets.size(); i++)
		{
			tBullet = mBullets.at(i);
			if (tBullet->getIsAlive())
			{
				if (enemy->checkCollisionBulletToParts(tBullet))
				{
					tBullet->setIsAlive(false);
				}//collision
			}//Bullet is Alive ?
		}//loop Bullets 
	}//Bullets Count > 0 ?
}

void CBulletPattern::checkCollisionActor(CActor * actor)
{
	if (mBullets.size() > 0)
	{
		CBullet * tBullet = nullptr;
		for (int i = 0; i < mBullets.size(); i++)
		{
			tBullet = mBullets.at(i);
			if (tBullet->getIsAlive())
			{
				if (utils::getCascadeBoundingBox(tBullet).intersectsCircle(
					actor->getPosition(), actor->getRedius()
				))
				{
					actor->hit();
					tBullet->setIsAlive(false);
				}
			}//Bullet is Alive ?
		}//loop Bullets 
	}//Bullets Count > 0 ?
}
