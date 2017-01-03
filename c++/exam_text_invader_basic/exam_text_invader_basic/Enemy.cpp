#include "stdafx.h"
#include "Enemy.h"
#include "config.h"
#include <Windows.h>
#include <iostream>

#include "EnemyBulletNormal.h"


CEnemy::CEnemy()
{
	mEnemyBullets.reserve(ENEMY_BULLET_COUNT);

	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets.push_back(new CEnemyBulletNormal());
		mEnemyBullets[ti]->SetAlive(false);
	}
	mCurBulletIndex = 0;

	mDirX = DIR_RIGHT;
	//-----------------------------------------

}


CEnemy::~CEnemy()
{
}


void CEnemy::Update()
{
	return;
	if (DIR_RIGHT == mDirX)
	{
		if (mX < WIDTH - 1)
		{
			mX = mX + 1;
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
			mX = mX - 1;
		}
		else
		{
			mDirX = DIR_RIGHT;
		}
	}



	int ti = 0;
	if (0 == mDelay)
	{
		mDelay = GetTickCount();
	}

	mTemp = GetTickCount();
	if (mTemp - mDelay > ENEMY_BULLET_INTERVAL)
	{
		if (false == mEnemyBullets[mCurBulletIndex]->GetAlive())
		{
			mEnemyBullets[mCurBulletIndex]->SetPositionForFire(this->mX, this->mY + 1);
			mEnemyBullets[mCurBulletIndex]->SetAlive(true);

			if (mCurBulletIndex < ENEMY_BULLET_COUNT - 1)
			{
				mCurBulletIndex++;
			}
			else
			{
				mCurBulletIndex = 0;
			}
		}

		mDelay = mTemp;
	}

	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti]->Update();
	}
}

void CEnemy::Clean(char * tpPixel)
{
	CUnit::Clean(tpPixel);
	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti]->Clean(tpPixel);
	}
}



void CEnemy::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY * WIDTH + mX) = '#';
	}
	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti]->Display(tpPixel);
	}
}


bool CEnemy::DoCollisionBulletWithActor(CActor * pPlayer)
{
	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		tResult = mEnemyBullets[ti]->DoCollisionWithActor(pPlayer);
		if (true == tResult)
		{
			break;
		}
	}

	return tResult;
}

void CEnemy::Destroy()
{
	delete this;
}



