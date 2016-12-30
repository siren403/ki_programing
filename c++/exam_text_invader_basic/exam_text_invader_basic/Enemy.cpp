#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::SetUp(int tWidth, int tHeight)
{
	CCharacter::SetUp(tWidth, tHeight);
	mX = tWidth / 2;
	mY = 0;
	mDir = DIR_RIGHT;
}

void CEnemy::Display(char * tpPixel)
{
	*(tpPixel + mY*mWidth + mX) = '#';
}

void CEnemy::Move()
{
	if (DIR_RIGHT == mDir)
	{
		if (mX < mWidth - 1)
		{
			mX = mX + 1;
		}
		else
		{
			mDir = DIR_LEFT;
		}
	}
	if (DIR_LEFT == mDir)
	{
		if (mX > 0)
		{
			mX = mX - 1;
		}
		else
		{
			mDir = DIR_RIGHT;
		}
	}
}
