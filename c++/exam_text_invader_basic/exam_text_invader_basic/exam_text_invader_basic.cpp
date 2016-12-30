// exam_text_invader_basic.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <conio.h>//console and port I/O 키입력
#include <iostream>
#include <Windows.h>

#include <time.h>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace std;

#define WIDTH 80
#define HEIGHT 24



void ClearScreen(int tX, int tY);


int main()
{
	//Create
	srand((unsigned int)time(NULL));

	char tPixel[HEIGHT][WIDTH] = { 0 };

	CPlayer tPlayer;
	CEnemy tEnemy;
	CBullet tPlayerBullet;
	CBullet tEnemyBullet;


	int tRow = 0;
	int tCol = 0;


	//Setup
	tPlayer.SetUp(WIDTH, HEIGHT);
	tEnemy.SetUp(WIDTH, HEIGHT);
	tPlayerBullet.SetUp(WIDTH, HEIGHT);
	tEnemyBullet.SetUp(WIDTH, HEIGHT);

	tEnemyBullet.SetX(WIDTH / 2);
	tEnemyBullet.SetY(1);
	tEnemyBullet.SetDir(CBullet::DIR_DOWN);
	tPlayerBullet.SetX(WIDTH / 2);
	tPlayerBullet.SetY(HEIGHT - 1 - 1);
	tPlayerBullet.SetDir(CBullet::DIR_UP);


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
		tEnemy.Clean(*tPixel);

		tPlayerBullet.Clean(*tPixel);
		tEnemyBullet.Clean(*tPixel);


		//Update
		int tFire = rand() % 6 + 1;
		if (tEnemyBullet.GetIsLife() == false && 1 == tFire)
		{
			//발사지점
			tEnemyBullet.SetX(tEnemy.GetX());
			tEnemyBullet.SetY(1);

			//발사됐는지 여부
			tEnemyBullet.Shot();
		}

		tEnemy.Move();
		
		
		tKey = 0;
		if (0 != _kbhit())//입력된 키가 있으면
		{
			tKey = _getch();//입력된 키값 받아옴

			//게임종료
			switch (tKey)
			{
			case 'Q':
			case 'q':
			{
				tIsEnd = true;
			}
			break;

		
			case 'M':
			case 'm':
			{
				//발사지점
				tPlayerBullet.SetX(tPlayer.GetX());
				tPlayerBullet.SetY(HEIGHT - 1 - 1);

				//발사됐는지 여부
				tPlayerBullet.Shot();
			}

			}

			tPlayer.MoveActorWithInput(tKey);
		}


		
		tPlayerBullet.Move();
		tEnemyBullet.Move();

		//Display
		ClearScreen(0, 0);

		tPlayer.Display(*tPixel);
		tEnemy.Display(*tPixel);

		tPlayerBullet.Display(*tPixel);
		tEnemyBullet.Display(*tPixel);

		for (tRow = 0; tRow < HEIGHT; tRow++)
		{
			for (tCol = 0; tCol < WIDTH; tCol++)
			{
				cout << tPixel[tRow][tCol];
			}
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

