#include "stdafx.h"
#include "ActorBullet.h"
#include "config.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

CActorBullet::CActorBullet()
{
	mDisplayMark = '*';
}


CActorBullet::~CActorBullet()
{
}


void CActorBullet::Update()
{
	if (IsScreenOut() == false)
	{
		mX = mX + mDirX * mSpeedPower;
		mY = mY + mDirY * mSpeedPower;
	}
	else
	{
		mIsAlive = false;
	}
}

bool CActorBullet::DoCollisionWithEnemy(CEnemy * pEnemy)
{
	bool tResult = false;

	if (this->mX == pEnemy->GetX() && this->mY == pEnemy->GetY())
	{
		cout << "ActorBullet VS enemy Collision" << endl;

		tResult = true;
	}

	return tResult;
}

