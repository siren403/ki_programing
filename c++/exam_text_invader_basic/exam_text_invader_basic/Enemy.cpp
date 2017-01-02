#include "stdafx.h"
#include "Enemy.h"
#include "gamesettings.h"
#include <iostream>
#include <Windows.h>
#include <WinBase.h>

CEnemy::CEnemy()
{
	mEnemyBullets = new CEnemyBullet[ENEMY_BULLET_COUNT];

	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti].SetAlive(false);
	}
	mCurBulletIndex = 0;

	mDirX = DIR_RIGHT;

}


CEnemy::~CEnemy()
{
}


void CEnemy::Update()
{
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
		if (false == mEnemyBullets[mCurBulletIndex].GetAlive())
		{
			mEnemyBullets[mCurBulletIndex].SetPositionForFire(this->mX, this->mY + 1);
			mEnemyBullets[mCurBulletIndex].SetAlive(true);

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
		if (false != mEnemyBullets[ti].GetAlive())
		{
			mEnemyBullets[ti].Update();
		}
	}
}

void CEnemy::Clean(char * tpPixel)
{
	CCharacter::Clean(tpPixel);
	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti].Clean(tpPixel);
	}
}


void CEnemy::Display(char * tpPixel)
{
	*(tpPixel + mY * WIDTH + mX) = '#';
	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti].Display(tpPixel);
	}
}

void CEnemy::SetPlayer(CPlayer * tPlayer)
{
	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		mEnemyBullets[ti].SetTarget(tPlayer);
	}
}

bool CEnemy::DoCollisionBulletWithActor(CPlayer * pPlayer)
{
	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < ENEMY_BULLET_COUNT; ti++)
	{
		tResult = mEnemyBullets[ti].DoCollisionWithActor(pPlayer);
		if (true == tResult)
		{
			break;
		}
	}

	return tResult;
}

