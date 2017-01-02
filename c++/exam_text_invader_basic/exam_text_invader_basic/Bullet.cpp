#include "stdafx.h"
#include "Bullet.h"
#include "gamesettings.h"
#include "Enemy.h"

CBullet::CBullet()
{
	mMark = '*';
}


CBullet::~CBullet()
{
}

void CBullet::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY*WIDTH + mX) = mMark;
	}
}

void CBullet::SetPositionForFire(int tX, int tY)
{
	mX = tX;
	mY = tY;
}



void CBullet::SetAlive(bool tAlive)
{
	mIsAlive = tAlive;
}


bool CBullet::GetAlive()
{
	return mIsAlive;
}

