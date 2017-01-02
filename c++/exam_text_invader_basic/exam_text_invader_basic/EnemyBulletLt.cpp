#include "stdafx.h"
#include "EnemyBulletLt.h"
#include "gamesettings.h"

CEnemyBulletLt::CEnemyBulletLt()
{
	mX = WIDTH / 2;
	mY = 1;
	mDirY = 1;
}


CEnemyBulletLt::~CEnemyBulletLt()
{
}


void CEnemyBulletLt::Update()
{
	if (mY < HEIGHT - 1 && (mX >= 0 && mX <= WIDTH - 1))
	{
		mY = mY + 1;
		mX = mX - 1;
	}
	else
	{
		mIsAlive = false;
		mY = 0;
	}
}
