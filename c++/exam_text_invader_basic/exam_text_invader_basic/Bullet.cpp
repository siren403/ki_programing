#include "stdafx.h"
#include "Bullet.h"
#include "config.h"
#include "Enemy.h"

bool CBullet::IsScreenOut()
{
	bool tResult = false;

	if (mX < 0 || mX > WIDTH - 1
		|| mY < 0 || mY > HEIGHT - 1)
	{
		tResult = true;
	}

	return tResult;
}

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


