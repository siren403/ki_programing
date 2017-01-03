#include "stdafx.h"
#include "Bullet.h"
#include "config.h"
#include "Enemy.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY*WIDTH + mX) = '*';
	}
}

void CBullet::SetPositionForFire(int tX, int tY)
{
	mX = tX;
	mY = tY;
}

void CBullet::Destroy()
{
	delete this;
}


