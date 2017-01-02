// exam_text_invader_basic.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>//console and port I/O 키입력
#include <Windows.h>
#include <iostream>

#include <time.h>

#include "Player.h"
#include "Enemy.h"
#include "EnemyBullet.h"

#include "gamesettings.h"



using namespace std;

void ClearScreen(int tX, int tY);


int main()
{
	//Create

	srand((unsigned int)time(NULL));

	char tPixel[HEIGHT][WIDTH] = { 0 };


	CPlayer tPlayer;
	CEnemy tEnemys[TOTAL_ENEMY_COUNT];


	int tRow = 0;
	int tCol = 0;
	int ti = 0;

	//Setup
	tPlayer.SetUp(WIDTH / 3, HEIGHT - 1);
	tEnemys[0].SetUp(0 + 5, 0);
	tEnemys[1].SetUp(WIDTH - 5, 0);
	tEnemys[0].SetPlayer(&tPlayer);
	tEnemys[1].SetPlayer(&tPlayer);


	//Display Title
	cout << "스타워즈" << endl;
	Sleep(1000);


	//game loop
	bool tIsEnd = false;
	char tKey = 0;
	while (true)
	{
		//Clean
		tPlayer.Clean(*tPixel);
		for (ti = 0; ti < TOTAL_ENEMY_COUNT; ti++)
		{
			tEnemys[ti].Clean(&tPixel[0][0]);

		}
		
		tKey = 0;
		if (0 != _kbhit())//입력된 키가 있으면
		{
			tKey = _getch();//입력된 키값 받아옴

			//게임종료
			switch (tKey)
			{
			case 'Q':
			case 'q':
				tIsEnd = true;
				break;
			}
		}

		tPlayer.Update();
		for (ti = 0; ti < TOTAL_ENEMY_COUNT; ti++)
		{
			tEnemys[ti].Update();
		}


		//Display
		ClearScreen(0, 0);

		tPlayer.Display(*tPixel);
		for (ti = 0; ti < TOTAL_ENEMY_COUNT; ti++)
		{
			tEnemys[ti].Display(&tPixel[0][0]);
		}

		for (tRow = 0; tRow < HEIGHT; tRow++)
		{
			for (tCol = 0; tCol < WIDTH; tCol++)
			{
				cout << tPixel[tRow][tCol];
			}
		}

		//collision

		for (ti = 0; ti < TOTAL_ENEMY_COUNT; ti++)
		{
			if (true == tPlayer.DoCollisionBulletWithEnemy(&tEnemys[ti]))
			{
				//todo...

				break;
			}

			//todo : boss...
		}

		for (ti = 0; ti < TOTAL_ENEMY_COUNT; ti++)
		{
			if (true == tEnemys[ti].DoCollisionBulletWithActor(&tPlayer))
			{
				//todo...

				break;
			}

			//todo : boss...
		}

		if (true == tIsEnd)
		{
			break;
		}
	}

	//Destroy

    return 0;
}

void ClearScreen(int tX, int tY)
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

	SetConsoleCursorInfo(hOutput, &cci_old);
}

