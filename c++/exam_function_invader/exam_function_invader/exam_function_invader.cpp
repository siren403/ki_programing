// exam_starwars_20160617.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>
#include <iostream>

#include <Windows.h>

#include <time.h>

using namespace std;



#define WIDTH 80
#define HEIGHT 24


#define DIR_LEFT  0
#define DIR_RIGHT 1



void ClearScreen(int tX, int tY);


class CActor
{
private:
	int mX = 0;
	int mY = 0;

public:
	CActor();
	~CActor();

	void SetupActor();


	void MoveActorWithInput(char tKey);

	void CleanPixelForActor(char *tpPixel);
	void DisplayPixelForActor(char *tpPixel);

};
//
//void SetupActor(int *tpX, int *tpY);
//
//
//void MoveActorWithInput(char tKey, int *tpX, int *tpY);
//
//void CleanPixelForActor(char *tpPixel, int *tpX, int *tpY);
//void DisplayPixelForActor(char *tpPixel, int *tpX, int *tpY);
//

int main()
{


	//Create

	srand((unsigned int)time(NULL));

	char tPixel[HEIGHT][WIDTH] = { 0, };//화면 을 흉내내는거.

										//아군기는 A로 표시하자.
										//유저의 키입력을 받아 좌우 이동을 구현하자.

	int tActorX = 0;
	int tActorY = 0;



	int tEnemyX = 0;
	int tEnemyY = 0;
	int tEnemyDir = 0;


	int tEnemyBulletX = 0;
	int tEnemyBulletY = 0;
	bool tIsEnemyBulletLife = false;


	int tActorBulletX = 0;
	int tActorBulletY = 0;
	bool tIsActorBulletLife = false;


	int tRow = 0;
	int tCol = 0;










	SetupActor(&tActorX, &tActorY);



	tEnemyX = WIDTH / 2;
	tEnemyY = 0;
	tEnemyDir = DIR_RIGHT;


	tEnemyBulletX = WIDTH / 2;
	tEnemyBulletY = 1;
	tIsEnemyBulletLife = false;


	tActorBulletX = WIDTH / 2;
	tActorBulletY = HEIGHT - 1 - 1;
	tIsActorBulletLife = false;




	//Display Title
	cout << "스타워즈" << endl;
	Sleep(5000);


	//게임루프
	bool tIsEnd = false;
	char tKey = 0;
	while (true)
	{

		//Clean
		CleanPixelForActor(&tPixel[0][0], &tActorX, &tActorY);

		tPixel[tEnemyY][tEnemyX] = 0;
		tPixel[tEnemyBulletY][tEnemyBulletX] = 0;
		tPixel[tActorBulletY][tActorBulletX] = 0;

		//Update
		//발사할까 말까.
		int tFire = rand() % 6 + 1;
		if (1 == tFire)
		{
			//발사지점
			tEnemyBulletX = tEnemyX;
			tEnemyBulletY = 1;

			//발사됐는지 여부
			tIsEnemyBulletLife = true;
		}


		if (DIR_RIGHT == tEnemyDir)
		{
			if (tEnemyX < WIDTH - 1)
			{
				tEnemyX = tEnemyX + 1;
			}
			else
			{
				tEnemyDir = DIR_LEFT;
			}
		}


		if (DIR_LEFT == tEnemyDir)
		{
			if (tEnemyX < 0)
			{
				tEnemyX = tEnemyX - 1;
			}
			else
			{
				tEnemyDir = DIR_RIGHT;
			}
		}






		tKey = 0;
		if (0 != _kbhit())
		{
			tKey = _getch();


			MoveActorWithInput(tKey, &tActorX, &tActorY);

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
				tActorBulletX = tActorX;
				tActorBulletY = HEIGHT - 1 - 1;

				//발사됐는지 여부
				tIsActorBulletLife = true;

			}
			break;

			}
		}


		if (true == tIsEnemyBulletLife)
		{
			if (tEnemyBulletY < HEIGHT - 1)
			{
				tEnemyBulletY = tEnemyBulletY + 1;
			}
		}


		if (true == tIsActorBulletLife)
		{
			if (tActorBulletY > 0)
			{
				tActorBulletY = tActorBulletY - 1;
			}
		}



		//Display
		ClearScreen(0, 0);


		DisplayPixelForActor(&tPixel[0][0], &tActorX, &tActorY);



		tPixel[tEnemyY][tEnemyX] = '#';
		tPixel[tEnemyBulletY][tEnemyBulletX] = '|';
		tPixel[tActorBulletY][tActorBulletX] = '*';

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



void CActor::SetupActor(int *tpX, int *tpY)
{
	(*tpX) = WIDTH / 2;
	(*tpY) = HEIGHT - 1;
}



void CActor::MoveActorWithInput(char tKey, int *tpX, int *tpY)
{
	//좌
	switch (tKey)
	{
	case 'Z':
	case 'z':
	{
		if ((*tpX) > 0)
		{
			(*tpX) = (*tpX) - 1;
		}

	}
	break;

	//우
	case 'X':
	case 'x':
	{
		if ((*tpX) < WIDTH - 1)
		{
			(*tpX) = (*tpX) + 1;
		}

	}
	break;
	}
}

void CActor::CleanPixelForActor(char *tpPixel, int *tpX, int *tpY)
{
	*(tpPixel + (*tpY)*WIDTH + (*tpX)) = 0;
}

void CActor::DisplayPixelForActor(char *tpPixel, int *tpX, int *tpY)
{
	*(tpPixel + (*tpY)*WIDTH + (*tpX)) = 'A';
}