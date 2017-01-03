#include "stdafx.h"
#include "Enemy.h"
#include "config.h"
#include <Windows.h>
#include <iostream>

#include "EnemyBulletNormal.h"


CEnemy::CEnemy()
{
	mEnemyBullets.reserve(ENEMY_BULLET_COUNT);
	mCurBulletIndex = 0;

	mDirX = DIR_RIGHT;

}


CEnemy::~CEnemy()
{
}


void CEnemy::Update()
{
	//Move
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

	//Shotting
	if (mEnemyBullets.size() == 0)
	{
		return;
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

			if (mCurBulletIndex < mEnemyBullets.size() - 1)
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

	for (ti = 0; ti < mEnemyBullets.size(); ti++)
	{
		mEnemyBullets[ti]->Update();
	}
}

void CEnemy::Clean(char * tpPixel)
{
	CUnit::Clean(tpPixel);
	if (mEnemyBullets.size() > 0)
	{
		int ti = 0;
		for (ti = 0; ti < mEnemyBullets.size(); ti++)
		{
			mEnemyBullets[ti]->Clean(tpPixel);
		}
	}
}



void CEnemy::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY * WIDTH + mX) = '#';
	}
	if (mEnemyBullets.size() > 0)
	{
		int ti = 0;
		for (ti = 0; ti < mEnemyBullets.size(); ti++)
		{
			mEnemyBullets[ti]->Display(tpPixel);
		}
	}

}


bool CEnemy::DoCollisionBulletWithActor(CActor * pPlayer)
{
	bool tResult = false;
	if (mEnemyBullets.size() > 0)
	{
		int ti = 0;
		
		for (ti = 0; ti < mEnemyBullets.size(); ti++)
		{
			tResult = mEnemyBullets[ti]->DoCollisionWithActor(pPlayer);
			if (true == tResult)
			{
				break;
			}
		}
	}
	return tResult;
}

void CEnemy::AddBullet(CEnemyBullet * tpEnemyBullet)
{
	mEnemyBullets.push_back(tpEnemyBullet);
	mEnemyBullets.back()->SetAlive(false);
}


void CEnemy::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mEnemyBullets.size(); ti++)
	{
		mEnemyBullets[ti]->Destroy();
	}
	mEnemyBullets.clear();

	delete this;
}



