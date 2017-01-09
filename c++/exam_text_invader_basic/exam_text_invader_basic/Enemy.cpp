#include "stdafx.h"
#include "Enemy.h"
#include "config.h"
#include <iostream>

#include "EnemyBulletNormal.h"


CEnemy::CEnemy()
{
	mDisplayMark = '#';
	mEnemyBullets.reserve(ENEMY_BULLET_COUNT);
	mCurBulletIndex = 0;

}


CEnemy::~CEnemy()
{
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

void CEnemy::Update()
{
	Shot();
}

void CEnemy::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY * WIDTH + mX) = mDisplayMark;
	}
	if (mEnemyBullets.size() > 0)
	{
		int ti = 0;
		for (ti = 0; ti < mEnemyBullets.size(); ti++)
		{
			if (mEnemyBullets[ti]->GetAlive() == true)
			{
				mEnemyBullets[ti]->Display(tpPixel);
			}
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
	tpEnemyBullet->SetAlive(false);
	mEnemyBullets.push_back(tpEnemyBullet);
}

void CEnemy::SetBulletInterval(unsigned int tInterval)
{
	mTimer.SetInterval(tInterval);
}

void CEnemy::Shot()
{
	//Shotting
	if (mEnemyBullets.size() > 0)
	{
		//mTimer.Init();

		mTimer.Update();
		bool first = false;
		if (mTimer.Check())
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
		}
	}

	int ti = 0;
	for (ti = 0; ti < mEnemyBullets.size(); ti++)
	{
		if (mEnemyBullets[ti]->GetAlive() == true)
		{
			mEnemyBullets[ti]->Update();
		}
	}
}



void CEnemy::Destroy()
{
	

	delete this;
}



