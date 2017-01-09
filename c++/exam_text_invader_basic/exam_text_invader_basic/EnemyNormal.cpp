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

	//Move
	if (mX >= mStartPositionX + mMoveWidth || mX <= mStartPositionX - mMoveWidth)
	{
		mDirX = -mDirX;
		mY = mY + mDirY * mSpeedPower;
		if (mY >= HEIGHT * 0.3f || mY <= 1)
		{
			mDirY = -mDirY;
			/*mIsAlive = false;*/
		}
	}

	mX = mX + mDirX * mSpeedPower;

	Shot();
}

void CEnemyNormal::SetUp(int tX, int tY)
{
	CUnit::SetUp(tX, tY);
	mStartPositionX = mX;
}

void CEnemyNormal::SetMoveWidth(int tMoveWidth)
{
	mMoveWidth = tMoveWidth;
}

