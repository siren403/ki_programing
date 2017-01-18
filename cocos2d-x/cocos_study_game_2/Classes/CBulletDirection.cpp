#include "CBulletDirection.h"


CBulletDirection * CBulletDirection::create(Sprite * tSprite)
{
	auto tBullet = CBulletDirection::create();
	if (tBullet != nullptr)
	{
		tBullet->mSprite = tSprite;
		tBullet->lateInit();
	}
	return tBullet;
}

bool CBulletDirection::lateInit()
{
	if (!CBullet::lateInit())
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
