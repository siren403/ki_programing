#include "stdafx.h"
#include "GameManager.h"

#include <conio.h>//console and port I/O 키입력
#include <Windows.h>
#include <iostream>

#include <time.h>

#include "EnemyBulletNormal.h"
#include "EnemyBulletPattern.h"


GameManager::GameManager()
{
	srand((unsigned int)time(NULL));
	system("mode con: cols=80 lines=24");


	mStateActions[GameManager::STATE_INIT] = &GameManager::Init;
	mStateActions[GameManager::STATE_TITLE] = &GameManager::Title;
	mStateActions[GameManager::STATE_UPDATE] = &GameManager::Update;
	mStateActions[GameManager::STATE_DISPLAY] = &GameManager::Display;
	mStateActions[GameManager::STATE_QUIT] = &GameManager::Quit;

	mCurrentState = GameManager::STATE_INIT;

}

GameManager::~GameManager()
{

}


void GameManager::Init()
{
	mActor.SetUp(WIDTH / 2, HEIGHT - 1);

	mEnemys.reserve(5);
	mEnemys.push_back(new CEnemy());
	mEnemys.back()->SetUp(WIDTH / 2, 0);

	CEnemyBulletPattern *tpBulletPattern = NULL;

	tpBulletPattern = new CEnemyBulletPattern();
	tpBulletPattern
		->AddBullet(new CEnemyBulletNormal(1, 1, 2))
		.AddBullet(new CEnemyBulletNormal(-1, 1, 2))
		.AddBullet(new CEnemyBulletNormal(0, 1, 2));

	mEnemys.back()->AddBullet(tpBulletPattern);


	mCurrentState = GameManager::STATE_TITLE;
}

void GameManager::Title()
{
	cout << "스타워즈" << endl;
	Sleep(1000);
	mCurrentState = GameManager::STATE_UPDATE;
}
void GameManager::Update()
{
	mActor.Clean(*tPixel);
	int ti = 0;
	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		mEnemys[ti]->Clean(&tPixel[0][0]);
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
			mCurrentState = GameManager::STATE_QUIT;
			return;
		}
	}

	mActor.Update();
	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		mEnemys[ti]->Update();
	}


	//Collision

	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		if (true == mActor.DoCollisionBulletWithEnemy(mEnemys[ti]))
		{
			//todo...
			mEnemys[ti]->SetAlive(false);
			break;
		}

		//todo : boss...
	}

	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		if (true == mEnemys[ti]->DoCollisionBulletWithActor(&mActor))
		{
			//todo...

			break;
		}

		//todo : boss...
	}



	mCurrentState = GameManager::STATE_DISPLAY;
}

void GameManager::Display()
{

	ClearScreen(0, 0);

	mActor.Display(*tPixel);
	int ti = 0;
	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		mEnemys[ti]->Display(&tPixel[0][0]);
	}

	for (mRow = 0; mRow < HEIGHT; mRow++)
	{
		for (mCol = 0; mCol < WIDTH; mCol++)
		{
			cout << tPixel[mRow][mCol];
		}
		cout << endl;
	}

	Sleep(1000/30);

	mCurrentState = GameManager::STATE_UPDATE;
}

void GameManager::Quit()
{
	mIsPlaying = false;
	int ti = 0;
	for (int ti = 0; ti < mEnemys.size(); ti++)
	{
		mEnemys[ti]->Destroy();
	}

	//delete ...
}


void GameManager::Play()
{
	mIsPlaying = true;
	while (mIsPlaying)
	{
		(this->*mStateActions[mCurrentState])();
	}
}

void GameManager::ClearScreen(int tX, int tY)
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

