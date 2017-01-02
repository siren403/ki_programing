#include "stdafx.h"
#include "PlayerBullet.h"
#include "gamesettings.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

CPlayerBullet::CPlayerBullet()
{
	mMark = '*';
	mX = WIDTH / 2;
	mY = HEIGHT - 1 - 1;
	mDirY = -1;
	mDirX = 0;
	mSpeedPower = 1;
}


CPlayerBullet::~CPlayerBullet()
{
}


void CPlayerBullet::Update()
{
	if (true == mIsAlive)
	{
		if (mY < HEIGHT - 1 || mY > 0)
		{
			mX = mX + mDirX * mSpeedPower;
			mY = mY + mDirY * mSpeedPower;
		}
		else
		{
			mIsAlive = false;
		}
	}
}

bool CPlayerBullet::DoCollisionWithEnemy(CEnemy * pEnemy)
{
	bool tResult = false;

	if (this->mX == pEnemy->GetX() && this->mY == pEnemy->GetY())
	{
		cout << "ActorBullet VS enemy Collision" << endl;

		tResult = true;
	}

	return tResult;
}