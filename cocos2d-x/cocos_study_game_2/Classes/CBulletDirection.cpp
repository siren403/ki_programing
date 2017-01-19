#include "CBulletDirection.h"



bool CBulletDirection::init()
{
	if (!CBullet::init())
	{
		return false;
	}


	return true;
}


void CBulletDirection::bulletUpdate(float dt)
{
	Vec2 tPos = this->getPosition();

	tPos.x += mCurrenDir.x * (mCurrentSpeed * dt);
	tPos.y += mCurrenDir.y * (mCurrentSpeed * dt);
	this->setPosition(tPos);
}
