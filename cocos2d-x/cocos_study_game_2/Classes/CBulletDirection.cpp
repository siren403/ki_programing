#include "CBulletDirection.h"



bool CBulletDirection::init()
{
	if (!CBullet::init())
	{
		return false;
	}

	mSprite = Sprite::create("bullet.png");
	mSprite->setScale(0.5f);
	this->addChild(mSprite);

	return true;
}


void CBulletDirection::bulletUpdate(float dt)
{
	Vec2 tPos = this->getPosition();

	tPos.x += mCurrenDir.x * (mCurrentSpeed * dt);
	tPos.y += mCurrenDir.y * (mCurrentSpeed * dt);
	this->setPosition(tPos);
}
