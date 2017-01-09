#include "stdafx.h"
#include "EnemyBulletNormal.h"
#include <iostream>

using namespace std;

CEnemyBulletNormal::CEnemyBulletNormal()
{
	mSpeedPower = 2;
	mDirX = 0;
	mDirY = 1;
}

CEnemyBulletNormal::CEnemyBulletNormal(int tDirX, int tDirY, int tSpeedPower)
{
	mDirX = tDirX;
	mDirY = tDirY;
	mSpeedPower = tSpeedPower;
}


CEnemyBulletNormal::~CEnemyBulletNormal()
{

}

void CEnemyBulletNormal::Update()
{
	mX = mX + mDirX * mSpeedPower;
	mY = mY + mDirY * mSpeedPower;

	if (IsScreenOut())
	{
		mIsAlive = false;
		mX = 0;
		mY = 0;
	}
}

