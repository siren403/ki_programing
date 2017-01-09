#include "stdafx.h"
#include "ActorBulletCurve.h"
#include "config.h"
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.14f

CActorBulletCurve::CActorBulletCurve()
{
	mDisplayMark = '^';
}


CActorBulletCurve::~CActorBulletCurve()
{
}

void CActorBulletCurve::Update()
{
	unsigned int tCurrentTime = GetTickCount();

	mY = mY + mDirY * mSpeedPower;
	mX = mX + (cos((PI * 2) * (tCurrentTime - ShotTime) * 0.001f) * mRadius) * mDirX;
	mY = mY + -abs(sin((PI * 2) * (tCurrentTime - ShotTime) * 0.001f) * mRadius);

	if (mDirX == 1)
	{
		mX = mX + 1;
	}

	if (IsScreenOut())
	{
		mIsAlive = false;
		mX = 0;
		mY = 0;
	}
}


void CActorBulletCurve::SetPositionForFire(int tX, int tY)
{
	CBullet::SetPositionForFire(tX, tY);
	ShotTime = GetTickCount();
}

void CActorBulletCurve::SetRadius(int tRadius)
{
	mRadius = tRadius;
}
