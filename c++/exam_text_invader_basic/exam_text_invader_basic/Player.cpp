#include "stdafx.h"
#include "Player.h"
#include <conio.h>//console and port I/O 키입력
#include <Windows.h>
#include "gamesettings.h"

CPlayer::CPlayer()
{
	mPlayerBullets = new CPlayerBullet[PLAYER_BULLET_COUNT];

	int ti = 0;
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		mPlayerBullets[ti].SetAlive(false);
	}
	mCurBulletIndex = 0;
}


CPlayer::~CPlayer()
{
}


void CPlayer::Update()
{
	mKey = 0;
	if (0 != _kbhit())//입력된 키가 있으면
	{
		mKey = _getch();//입력된 키값 받아옴

		switch (mKey)
		{
		case 'M':
		case 'm':
			
			if (false == mPlayerBullets[mCurBulletIndex].GetAlive())
			{
				mPlayerBullets[mCurBulletIndex].SetPositionForFire(this->mX, this->mY - 1);

				mPlayerBullets[mCurBulletIndex].SetAlive(true);

				if (mCurBulletIndex < PLAYER_BULLET_COUNT - 1)
				{
					mCurBulletIndex++;
				}
				else
				{
					mCurBulletIndex = 0;
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
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		if (true == mPlayerBullets[ti].GetAlive())
		{
			mPlayerBullets[ti].Update();
		}
	}
}

void CPlayer::Clean(char * tpPixel)
{
	CCharacter::Clean(tpPixel);
	int ti = 0;
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		mPlayerBullets[ti].Clean(tpPixel);
	}
}

void CPlayer::Display(char * tpPixel)
{
	*(tpPixel + mY * WIDTH + mX) = 'A';
	int ti = 0;
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		mPlayerBullets[ti].Display(tpPixel);
	}
}


bool CPlayer::DoCollisionBulletWithEnemy(CEnemy * pEnemy)
{
	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < PLAYER_BULLET_COUNT; ti++)
	{
		tResult = mPlayerBullets[ti].DoCollisionWithEnemy(pEnemy);
		
		if (true == tResult)
		{
			break;
		}
	}

	return tResult;
}


