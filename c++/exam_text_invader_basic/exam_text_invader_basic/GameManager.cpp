#include "stdafx.h"
#include "GameManager.h"

#include <conio.h>//console and port I/O 키입력
#include <Windows.h>
#include <iostream>

#include <time.h>
#include "EnemyFactorySample0.h"
#include "EnemyFactorySample1.h"
#include "EnemyFactorySample2.h"

#define SCREEN_SETTING false

CGameManager::CGameManager()
{
	srand((unsigned int)time(NULL));
	
	if(SCREEN_SETTING)
		system("mode con: cols=80 lines=24");

	mStateActions[CGameManager::STATE_INIT] = &CGameManager::Init;
	mStateActions[CGameManager::STATE_TITLE] = &CGameManager::Title;
	mStateActions[CGameManager::STATE_UPDATE] = &CGameManager::Update;
	mStateActions[CGameManager::STATE_DISPLAY] = &CGameManager::Display;
	mStateActions[CGameManager::STATE_QUIT] = &CGameManager::Quit;

	mCurrentState = CGameManager::STATE_INIT;

}

CGameManager::~CGameManager()
{

}


void CGameManager::Init()
{
	mActor.SetUp(WIDTH / 2, HEIGHT - 1);
	
	int ti = 0;
	CActorBullet * tpActorBullet = NULL;

	for (ti = 0; ti < ACTOR_BULLET_COUNT; ti++)
	{
		tpActorBullet = new CActorBullet();
		tpActorBullet->SetDirectionAndSpeedPower(0, -1, 1);
		mActor.AddBullet(tpActorBullet);
	}

	mEnemyFactorys.reserve(5);
	mEnemyFactorys.push_back(new CEnemyFactorySample0());
	mEnemyFactorys.push_back(new CEnemyFactorySample1());
	mEnemyFactorys.push_back(new CEnemyFactorySample2());

	SetFactory(0);

	if (mEnemyFactorys.size() > 0)
	{
		mCurrentState = CGameManager::STATE_TITLE;
	}
	else
	{
		mCurrentState = CGameManager::STATE_QUIT;
	}
}

void CGameManager::Title()
{
	cout << "스타워즈" << endl;
	Sleep(1000);
	mCurrentState = CGameManager::STATE_UPDATE;
}
void CGameManager::Update()
{
	mActor.Clean(*tPixel);
	int ti = 0;
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		(*mEnemys)[ti]->Clean(&tPixel[0][0]);
	}

	mKey = 0;
	if (0 != _kbhit())//입력된 키가 있으면
	{
		mKey = _getch();//입력된 키값 받아옴

						//게임종료
		switch (mKey)
		{
		case 'Q':
		case 'q':
			mCurrentState = CGameManager::STATE_QUIT;
			return;
		}
	}

	mActor.Update();
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if ((*mEnemys)[ti]->GetAlive() == true)
		{
			(*mEnemys)[ti]->Update();
			if ((*mEnemys)[ti]->GetX() < 0)
			{
				(*mEnemys)[ti]->SetX(0);
			}
			else if ((*mEnemys)[ti]->GetX() > WIDTH - 1)
			{
				(*mEnemys)[ti]->SetX(WIDTH - 1);
			}
		}
	}

	//Collision

	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if (true == mActor.DoCollisionBulletWithEnemy((*mEnemys)[ti]))
		{
			//todo...
			(*mEnemys)[ti]->SetAlive(false);
			break;
		}
		//todo : boss...
	}

	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if (true == (*mEnemys)[ti]->DoCollisionBulletWithActor(&mActor))
		{
			//todo...
			mActor.SetAlive(false);
			break;
		}
		//todo : boss...
	}

	mCurrentState = CGameManager::STATE_DISPLAY;

	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if ((*mEnemys)[ti]->GetAlive())
		{
			return;
		}
	}

	mCurrentFactory++;

	mEnemyFactorys[mCurrentFactory]->DoSetting(*this);
}

void CGameManager::Display()
{

	ClearScreen(0, 0);

	mActor.Display(*tPixel);
	int ti = 0;
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		(*mEnemys)[ti]->Display(&tPixel[0][0]);
	}

	for (mRow = 0; mRow < HEIGHT; mRow++)
	{
		for (mCol = 0; mCol < WIDTH; mCol++)
		{
			cout << tPixel[mRow][mCol];
		}

		//if (SCREEN_SETTING)
			//cout << endl;
	}
	if (SCREEN_SETTING)
		Sleep(1000 / 30);

	mCurrentState = CGameManager::STATE_UPDATE;
}

void CGameManager::Quit()
{
	mIsPlaying = false;
	mEnemys = NULL;
	int ti = 0;
	for (int ti = 0; ti < mEnemyFactorys.size(); ti++)
	{
		mEnemyFactorys[ti]->Destroy();
	}

	//delete ...
}


void CGameManager::Play()
{
	mIsPlaying = true;
	while (mIsPlaying)
	{
		(this->*mStateActions[mCurrentState])();
	}
}

void CGameManager::SetEnemys(vector<CEnemy*>* tpEnemys)
{
	mEnemys = tpEnemys;
}

void CGameManager::SetFactory(int tIndex)
{
	mCurrentFactory = tIndex;
	mEnemyFactorys[mCurrentFactory]->DoSetting(*this);
}

void CGameManager::ClearScreen(int tX, int tY)
{
	CONSOLE_CURSOR_INFO cci;
	CONSOLE_CURSOR_INFO cci_old;

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hOutput, &cci_old);

	cci.bVisible = FALSE;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);

	COORD cd;
	cd.X = tX;
	cd.Y = tY;

	SetConsoleCursorPosition(hOutput, cd);

}

