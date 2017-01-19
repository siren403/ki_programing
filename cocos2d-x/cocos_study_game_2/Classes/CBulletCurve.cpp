#include "CBulletCurve.h"

#define PI 3.14

void CBulletCurve::bulletUpdate(float dt)
{

	mAccumulateTime += dt;
	Vec2 tVec = this->getPosition();

	tVec.x += (mCurrenDir.x * mCurrentSpeed) * dt;

	tVec.x += abs(cos((PI * 2) * mAccumulateTime) * mRadius) * dt;
	tVec.y += (sin((PI * 2) * mAccumulateTime) * mRadius) * mCurrenDir.y * dt;

	this->setPosition(tVec);
}

void CBulletCurve::setRadius(float tRadius)
{
	mRadius = tRadius;
}

void CBulletCurve::shot(Vec2 tPos)
{
	CBullet::shot(tPos);
	mAccumulateTime = 0.25;
}

