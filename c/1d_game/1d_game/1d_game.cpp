// 1d_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


using namespace std;

	

struct Player
{
	int Position = 0;
	int Health = 0;
};

struct Slime
{
	int Position = 0;
	int Health = 0;
	int Order = 0;
};

int DrawTitle();
void PlayerToMove(Player *tPlayer, int tMap[], int tIndex);

int main()
{

	int tGameState = 0;
	int Map[5] = { 0,0,0,0,0 };
	char tIsQuit = 'n';
	
	Player *tPlayer = NULL;
	Slime *tNormalSlime = NULL;
	Slime *tBossSlime = NULL;

	tPlayer = new Player();
	tPlayer->Health = 5;

	tNormalSlime = new Slime();
	tBossSlime = new Slime();

	while ('n' == tIsQuit)
	{
		switch (tGameState)
		{
		case 0://타이틀
			tGameState = DrawTitle();
			break;
		case 1:


			break;
		case 2://종료
			printf("정말 종료하시겠습니까?(y/n): ");
			cin >> tIsQuit;
			if ('n' == tIsQuit)
			{
				tGameState = 0;
			}
			break;
		}
		//system("cls");
	}

	if (tPlayer != NULL)
	{
		delete tPlayer;
		tPlayer = NULL;
	}
	if (tNormalSlime != NULL)
	{
		delete tNormalSlime;
		tNormalSlime = NULL;
	}
	if (tBossSlime != NULL)
	{
		delete tBossSlime;
		tBossSlime = NULL;
	}

    return 0;
}

int DrawTitle()
{
	int tInput = 0;

	printf("용사는 일차원\n\n");
	printf("1.게임 시작\n");
	printf("2.종료\n");

	cin >> tInput;

	return tInput;
}

void PlayerToMove(Player *tPlayer, int tMap[],int tIndex)
{
	if (tPlayer != NULL && tMap != NULL)
	{
	}
}
