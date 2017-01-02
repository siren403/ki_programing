#include "stdafx.h"
#include "EnemyBullet.h"
#include "Player.h"
#include <iostream>
#include <math.h>
#include "Player.h"
#include "gamesettings.h"

using namespace std;

CEnemyBullet::CEnemyBullet()
{
	mMark = '|';
	mX = WIDTH / 2;
	mY = 1;
	mDirX = 0;
	mDirY = 1;
	mSpeedPower = 2;
}


CEnemyBullet::~CEnemyBullet()
{
}


void CEnemyBullet::Update()
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

void CEnemyBullet::SetTarget(CPlayer * tpPlayer)
{
	mPlayer = tpPlayer;
}

void CEnemyBullet::SetPositionForFire(int tX, int tY)
{
	mX = tX;
	mY = tY;
}

bool CEnemyBullet::DoCollisionWithActor(CPlayer * pPlayer)
{
	bool tResult = false;

	if (this->mX == pPlayer->GetX() && this->mY == pPlayer->GetY())
	{
		cout << "EnemyBullet VS actor Collision" << endl;
		tResult = true;
		
	}

	return tResult;
}
