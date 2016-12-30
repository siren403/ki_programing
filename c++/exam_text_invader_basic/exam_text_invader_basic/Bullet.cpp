#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Display(char * tpPixel)
{
	char tChar = 0;

	switch (mDir)
	{
	case DIR_DOWN:
		tChar = '|';
		break;
	case DIR_UP:
		tChar = '*';
		break;
	}

	*(tpPixel + mY*mWidth + mX) = tChar;
}

void CBullet::Shot()
{
	mIsLife = true;
}

void CBullet::Move()
{
	if (true == mIsLife)
	{
		if (mY < mHeight - 1 || mY > 0)
		{
			mY = mY + mDir;
		}
		else
		{
			mIsLife = false;
		}
	}
}

void CBullet::SetDir(int tDir)
{
	mDir = tDir;
}

bool CBullet::GetIsLife()
{
	return mIsLife;
}

