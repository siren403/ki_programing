#include "stdafx.h"
#include "EnemyBulletHoming.h"
#include "config.h"
#include <math.h>

CEnemyBulletHoming::CEnemyBulletHoming()
{
}


CEnemyBulletHoming::~CEnemyBulletHoming()
{
}

void CEnemyBulletHoming::Update()
{
	if (mY < HEIGHT - 1)
	{
		if (mPlayer != NULL)
		{
			float tDistance = sqrt(((mPlayer->GetX() - mX)*(mPlayer->GetX() - mX)) +
				((mPlayer->GetY() - mY)*(mPlayer->GetY() - mY)));

			mDirX = ((mPlayer->GetX() - mX) / tDistance) * mSpeedPower;
			mDirY = ((mPlayer->GetY() - mY) / tDistance) * mSpeedPower;
		}
		mX = mX + mDirX * mSpeedPower;
		mY = mY + mDirY * mSpeedPower;
	}
	else
	{
		mIsAlive = false;
		mY = 0;
		mX = 0;
	}
}

CEnemyBulletHoming * CEnemyBulletHoming::SetTarget(CActor * tpPlayer)
{
	mPlayer = tpPlayer;
	return this;
}
