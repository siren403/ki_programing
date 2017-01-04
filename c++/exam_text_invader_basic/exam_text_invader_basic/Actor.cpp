#include "stdafx.h"
#include "Actor.h"
#include <conio.h>//console and port I/O 키입력
#include <Windows.h>
#include "config.h"

CActor::CActor()
{

	//mActorBullets = new CActorBullet[PLAYER_BULLET_COUNT];

	/*int ti = 0;
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		mActorBullets[ti].SetAlive(false);
	}
	mCurBulletIndex = 0;
*/
	mDisplayMark = 'A';
	mActorBullets.reserve(ACTOR_BULLET_COUNT);
	mCurBulletIndex = 0;
}

CActor::~CActor()
{
}

void CActor::Clean(char * tpPixel)
{
	CUnit::Clean(tpPixel);

	int ti = 0;
	for (ti = 0; ti < mActorBullets.size(); ti++)
	{
		mActorBullets[ti]->Clean(tpPixel);
	}
}

void CActor::Update()
{
	mKey = 0;
	if (0 != _kbhit())//입력된 키가 있으면
	{
		mKey = _getch();//입력된 키값 받아옴

		switch (mKey)
		{
		case 'M':
		case 'm':
			
			if (mActorBullets.size() > 0)
			{
				if (false == mActorBullets[mCurBulletIndex]->GetAlive())
				{
					mActorBullets[mCurBulletIndex]->SetPositionForFire(this->mX, this->mY - 1);

					mActorBullets[mCurBulletIndex]->SetAlive(true);

					if (mCurBulletIndex < ACTOR_BULLET_COUNT - 1)
					{
						mCurBulletIndex++;
					}
					else
					{
						mCurBulletIndex = 0;
					}

				}
			}
			break;
		case 'Z':
		case 'z':
			if (mX > 0)
			{
				mX = mX - 1;
			}
			break;
			//우
		case 'X':
		case 'x':
			if (mX < WIDTH - 1)
			{
				mX = mX + 1;
			}
			break;
		}
	}

	int ti = 0;
	for (ti = 0; ti < mActorBullets.size(); ti++)
	{
		if (true == mActorBullets[ti]->GetAlive())
		{
			mActorBullets[ti]->Update();
		}
	}
}



void CActor::Display(char * tpPixel)
{
	if (mIsAlive)
	{
		*(tpPixel + mY * WIDTH + mX) = mDisplayMark;
	}
	int ti = 0;
	for (ti = 0; ti < mActorBullets.size(); ti++)
	{
		if (mActorBullets[ti]->GetAlive() == true)
		{
			mActorBullets[ti]->Display(tpPixel);
		}
	}
}


bool CActor::DoCollisionBulletWithEnemy(CEnemy * pEnemy)
{
	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < mActorBullets.size(); ti++)
	{
		tResult = mActorBullets[ti]->DoCollisionWithEnemy(pEnemy);
		
		if (true == tResult)
		{
			break;
		}
	}

	return tResult;
}

void CActor::AddBullet(CActorBullet * tpActorBullet)
{
	tpActorBullet->SetAlive(false);
	mActorBullets.push_back(tpActorBullet);
}

void CActor::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mActorBullets.size(); ti++)
	{
		mActorBullets[ti]->Destroy();
	}
	mActorBullets.clear();
	delete this;
}


