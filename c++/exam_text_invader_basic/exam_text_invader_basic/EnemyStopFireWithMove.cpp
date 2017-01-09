#include "stdafx.h"
#include "EnemyStopFireWithMove.h"
#include <iostream>

using namespace std;

CEnemyStopFireWithMove::CEnemyStopFireWithMove()
{
	mDisplayMark = '+';
	mDirX = 1;
	mDirY = 0;
	mCurrentState = STATE_FIRE;
}


CEnemyStopFireWithMove::~CEnemyStopFireWithMove()
{
}

void CEnemyStopFireWithMove::Update()
{
	int ti = 0;
	for (ti = 0; ti < mEnemyBullets.size(); ti++)
	{
		if (mEnemyBullets[ti]->GetAlive() == true)
		{
			mEnemyBullets[ti]->Update();
		}
	}

	switch (mCurrentState)
	{
	case STATE_FIRE:
		Shot();
		if (mEnemyBullets[mCurBulletIndex]->GetAlive())
		{
			mCurrentState = STATE_MOVE;
		}
		break;
	case STATE_MOVE:

		if (mX >= WIDTH - 1 || mX <= 1)
		{
			mDirX = -mDirX;
		}
		mX = mX + mDirX * mSpeedPower;

		int ti = 0;
		for (ti = 0; ti < mEnemyBullets.size(); ti++)
		{
			if (mEnemyBullets[ti]->GetAlive())
			{
				return;
			}
		}
		mCurrentState = STATE_FIRE;
		break;
	}



}

void CEnemyStopFireWithMove::Shot()
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

	

}
