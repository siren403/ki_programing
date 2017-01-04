#include "stdafx.h"
#include "EnemyNormal.h"

#define DIR_LEFT -1
#define DIR_RIGHT 1

CEnemyNormal::CEnemyNormal()
{
	mDirX = DIR_RIGHT;
}

CEnemyNormal::~CEnemyNormal()
{
}

void CEnemyNormal::Update()
{
	/*if (DIR_RIGHT == mDirX)
	{
	if (mX < WIDTH - 1)
	{
	mDirX = DIR_RIGHT;
	}
	else
	{
	mDirX = DIR_LEFT;
	}
	}
	if (DIR_LEFT == mDirX)
	{
	if (mX > 0)
	{
	mDirX = DIR_LEFT;
	}
	else
	{
	mDirX = DIR_RIGHT;
	}
	}*/

	//Move
	if (mX >= WIDTH - 1 || mX <= 1)
	{
		mDirX = -mDirX;
		mY = mY + mSpeedPower;
		if (mY >= HEIGHT - 1)
		{
			mIsAlive = false;
		}
	}

	mX = mX + mDirX * mSpeedPower;


	Shot();
}

