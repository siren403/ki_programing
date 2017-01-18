#include "CBulletPattern.h"





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

void CBulletPattern::Shot(Vec2 tPos)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets.at(i)->setPosition(tPos);
		mBullets.at(i)->setIsAlive(true);
	}
}
