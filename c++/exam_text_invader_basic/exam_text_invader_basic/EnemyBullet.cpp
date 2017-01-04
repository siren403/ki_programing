#include "stdafx.h"
#include "EnemyBullet.h"
#include "Actor.h"
#include <iostream>
#include <math.h>
#include "config.h"

using namespace std;

CEnemyBullet::CEnemyBullet()
{
	mDisplayMark = '|';
	mDirX = 0;
	mDirY = 1;
	mSpeedPower = 2;
}


CEnemyBullet::~CEnemyBullet()
{
}


void CEnemyBullet::Update()
{
}


void CEnemyBullet::SetPositionForFire(int tX, int tY)
{
	mX = tX;
	mY = tY;
}

bool CEnemyBullet::DoCollisionWithActor(CActor * pPlayer)
{
	bool tResult = false;

	if (this->mX == pPlayer->GetX() && this->mY == pPlayer->GetY())
	{
		cout << "EnemyBullet VS actor Collision" << endl;
		tResult = true;
		
	}
	return tResult;
}


