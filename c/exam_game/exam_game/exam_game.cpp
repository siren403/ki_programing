// 1d_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

#define YES 'y'
#define NO 'n'

//State Values
#define TITLE 0
#define PLAY 1
#define QUIT 2
#define INIT 3

//Player,Monsters Kind
#define KIND_PLAYER 11
#define KIND_NORMAL_SLIME 12
#define KIND_BOSS_SLIME 13

#define MAP_LENGTH 5
#define MAX_HEALTH 10

using namespace std;

struct Player
{
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;

	int mPosition = 0;
};

struct Slime
{
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;

	char(*mDoBattle)(Player *tPlayer,Slime *tSlime) = NULL;
};

int DisplayTitle();
void PlayerToMove(Player *tPlayer, int tMap[],int tIndex);
void DrawMap(int tMap[]);
char CheckSlimeEncount(Player *tPlayer, int tMap[]);

void DoAttack(int tPower, int *tTargetCurrentHealth);

char DoNormalBattle(Player *tPlayer, Slime *tSlime);
int DoThrowDice(int tMaxNumber);

char DoBossBattle(Player *tPlayer, Slime *tSlime);
char CheckCompareCard(int tPlayerCard, int tSlimeCard);
void DisplayCard(int tCardValue);

void DisplayGauge(int tCurrentValue, int tMaxValue);


int main()
{
	
	srand(time(NULL));

	int tGameState = TITLE;//게임시작 시 타이틀 상태
	int tMap[MAP_LENGTH] = { 0 };//지정한 맵길이로 요소들 초기화
	int tInput = 0;//Input입력 받는 변수
	char tIsContinue = YES;

	Player *tPlayer = NULL;
	Slime *tNormalSlime = NULL;
	Slime *tBossSlime = NULL;

	tPlayer = new Player();
	tNormalSlime = new Slime();
	tBossSlime = new Slime();

	tPlayer->mHealth = 5;

	tNormalSlime->mHealth = 5;
	tNormalSlime->mDoBattle = DoNormalBattle;//주사위 게임

	tBossSlime->mHealth = 10;
	tBossSlime->mDoBattle = DoBossBattle;//가위,바위,보


	while (NO != tIsContinue)
	{
		switch (tGameState)
		{
		case TITLE://타이틀
			tGameState = DisplayTitle();
			break;
		case INIT://재시작 시 초기화 값
			tPlayer->mCurrentHealth = tPlayer->mHealth;
			tPlayer->mPower = 1;

			tNormalSlime->mCurrentHealth = tNormalSlime->mHealth;
			tNormalSlime->mPower = 1;

			tBossSlime->mCurrentHealth = tBossSlime->mHealth;
			tBossSlime->mPower = 2;

			
			//플레이어 초기위치로 이동
			PlayerToMove(tPlayer, tMap, 0);
			//2번에는 일반 슬라임이 있다. 
			tMap[2] = KIND_NORMAL_SLIME;
			//4번에는 보스 슬라임이 있다.
			tMap[4] = KIND_BOSS_SLIME;


			tGameState = PLAY;
			break;
		case PLAY:
			DrawMap(tMap);

			if (CheckSlimeEncount(tPlayer, tMap))//적과 마주침
			{
				int tSlimeKind = 0;
				Slime *tSlime = NULL;

				//현재 플레이어 위치+1의 마주보는 슬라임 종류
				tSlimeKind = tMap[tPlayer->mPosition + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t[ 일반 슬라임이 나타났다. ]\n\n");
					tSlime = tNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t[ 보스 슬라임이 나타났다. ]\n\n");
					tSlime = tBossSlime;
				}

				printf("1.싸움을 건다!!\n2.도망친다..\n");
				cin >> tInput;

				if (tInput == 1)
				{
					int tBattleResult = 0;
					//printf("\t[ 전투가 시작했다!! ]\n\n");
					tBattleResult = tSlime->mDoBattle(tPlayer, tSlime);

					if (tBattleResult == 1)//승리
					{
						//용사 체력 회복
						tPlayer->mCurrentHealth = tPlayer->mHealth;

						//슬라임이 있던 위치 초기화
						tMap[tPlayer->mPosition + 1] = 0;
						//다음 위치로 이동
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition + 1);
					}
					else if (tBattleResult == 0)//패배
					{
						printf("\n\n\t\t[ 용사는 죽었다... ]\n\n\n");
						
						tGameState = QUIT;
					}

					printf("Input Any Key\n");
					cin >> tInput;
				}
				else if (tInput == 2)
				{
					printf("\t[ 용사는 도망쳤다... ]\n");
					PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
				}
			}
			else//적과 마주치지 않음
			{
				if (tPlayer->mPosition != MAP_LENGTH - 1)//맵 끝에 도달하지 않았으면
				{
					printf("\t[ 어떻게 할까? ]\n\n");
					printf("1.전진하기\n2.돌아가기\n");
					cin >> tInput;

					if (tInput == 1)
					{
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition + 1);
					}
					else if (tInput == 2)
					{
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
					}
				}
				else
				{
					printf("\t[ 게임을 클리어하였습니다. ]\n\n");
					printf("Input Any Key\n");
					cin >> tInput;
					tGameState = QUIT;
				}
			}

			break;
		case QUIT://종료
			printf("\n\n\n계속하시겠습니까?(y/n): ");
			cin >> tIsContinue;
			if (YES == tIsContinue)
			{
				tGameState = 0;
			}
			break;
		}
		system("cls");
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

int DisplayTitle()
{
	int tInput = 0;


	printf("\n\n\t[ 용사는 일차원 ]\n\n\n");
	printf("1.게임 시작\n");
	printf("2.종료\n");

	cin >> tInput;

	if (tInput == 1)//시작 선택 시 상태를 초기화로 변경
	{
		tInput = INIT;
	}
	else//종료
	{
		tInput = QUIT;
	}

	return tInput;
}

void PlayerToMove(Player *tPlayer, int tMap[], int tIndex)
{
	if (tIndex >= 0 && tIndex < MAP_LENGTH)
	{
		tMap[tPlayer->mPosition] = 0;
		tMap[tIndex] = KIND_PLAYER;
		tPlayer->mPosition = tIndex;
	}
	else
	{
		int tInput = 0;

		printf("\t[ 이동 할 수 없다... ]\n");
		printf("Input Any Key\n");
		cin >> tInput;
	}

}

void DrawMap(int tMap[])
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n==");
	for (ti = 0; ti < MAP_LENGTH; ti++)
	{
		switch (tMap[ti])
		{
		case KIND_PLAYER:
			printf("[  PLAYER  ]==");
			break;
		case KIND_NORMAL_SLIME:
			printf("[  SLIME   ]==");
			break;
		case KIND_BOSS_SLIME:
			printf("[BOSS SLIME]==");
			break;
		case 0://없음
		default:
			printf("[          ]==");
			break;
		}
	}
	printf("\n");
	printf("====================================");
	printf("====================================");
	printf("\n\n");

}
char CheckSlimeEncount(Player *tPlayer, int tMap[])
{
	char tResult = 0;

	if (tPlayer != NULL && tPlayer->mPosition < MAP_LENGTH - 1)
	{
		if (tMap[tPlayer->mPosition + 1] != 0)
		{
			tResult = 1;
		}
	}
	return tResult;
}

void DoAttack(int tPower, int *tTargetCurrentHealth) 
{
	*tTargetCurrentHealth -= tPower;
	if (*tTargetCurrentHealth < 0)
	{
		*tTargetCurrentHealth = 0;
	}
}

char DoNormalBattle(Player *tPlayer, Slime *tSlime)
{
	int tInput = 0;
	int tDiceNumber = 0;

	char tResult = 0;

	printf("\t\t[주사위 배틀]\n");
	printf("\t눈금이 4이상이면 용사가 공격!\n");
	printf("\t눈금이 3이하면 슬라임이 공격한다.\n\n");

	while (1)
	{
		printf("\t[용사]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[슬라임]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("1. 주사위를 던진다.\n");
		cin >> tInput;

		printf("================================================\n\n");
		tDiceNumber = DoThrowDice(6);

		printf("\n\t   주사위 -> ");
		DisplayGauge(tDiceNumber, 6);
		printf("\n\n");

		if (4 <= tDiceNumber)//4이상 승리
		{
			printf("\t공격!!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.\n\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower,&tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t[ 슬라임을 잡았다!! ]\n\n");

				if (DoThrowDice(3) <= 3)
				{
					printf("\t\t[ 용사가 강해졌다. ]\n\n");
					tPlayer->mHealth += 2;
					tPlayer->mPower += 2;
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDiceNumber)//3이하 패배
		{
			printf("\t슬라임이 %d만큼 피해를 입혔다.\n\n", tSlime->mPower);
			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}
int DoThrowDice(int tMaxNumber)
{
	int tResult = 0;

	tResult = rand() % tMaxNumber + 1;
	//tResult = 4;

	return tResult;
}


char DoBossBattle(Player *tPlayer, Slime *tSlime)
{
	int tPlayerCard = 0;
	int tSlimeCard = 0;
	int tCompareResult = 0;

	char tResult = 0;

	printf("\n\t\t[ 가위,바위,보 게임 ]\n\n");
	printf("\t가위,바위,보를 내서 이긴쪽이 공격한다!\n\n\n");

	while (1)
	{
		printf("[용사]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[보스 슬라임]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("[1]:가위, [2]:바위, [3]:보\n\n");
		printf("선택하세요 : ");
		cin >> tPlayerCard;
		printf("\n================================================\n");


		tSlimeCard = DoThrowDice(3);

		tCompareResult = CheckCompareCard(tPlayerCard, tSlimeCard);

		printf("\n\t\t");
		printf("[용사]");
		DisplayCard(tPlayerCard);
		printf(" vs ");
		DisplayCard(tSlimeCard);
		printf("[슬라임]");
		printf("\n\n");

		
		if (0 == tCompareResult)//무승부
		{
			printf("\t\t\t비겼습니다.\n\n");
		}
		else if (1 == tCompareResult)//승리
		{
			printf("\t승리!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.\n\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower, &tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t[ 슬라임을 잡았다!! ]\n\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//패배
		{
			printf("\t패배...");
			printf("보스 슬라임이 %d만큼 피해를 입혔다.\n\n", tSlime->mPower);
			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

char CheckCompareCard(int tPlayerCard, int tSlimeCard)
{
	char tResult = 0;

	switch (tPlayerCard)
	{
	case 1://가위
		switch (tSlimeCard)
		{
		case 1:
			tResult = 0;
			break;
		case 2:
			tResult = 2;
			break;
		case 3:
			tResult = 1;
			break;
		}
		break;
	case 2://바위
		switch (tSlimeCard)
		{
		case 1:
			tResult = 1;
			break;
		case 2:
			tResult = 0;
			break;
		case 3:
			tResult = 2;
			break;
		}
		break;
	case 3://보
		switch (tSlimeCard)
		{
		case 1:
			tResult = 2;
			break;
		case 2:
			tResult = 1;
			break;
		case 3:
			tResult = 0;
			break;
		}
		break;
	}

	return tResult;
}
void DisplayCard(int tCardValue)
{
	switch (tCardValue)
	{
	case 1:
		printf("가위");
		break;
	case 2:
		printf("바위");
		break;
	case 3:
		printf("보");
		break;
	}
}


void DisplayGauge(int tCurrentValue, int tMaxValue)
{
	int ti = 0;

	for (ti = 0; ti < tCurrentValue; ti++)
	{
		printf("■");
	}
	for (ti = 0; ti < tMaxValue - tCurrentValue; ti++)
	{
		printf("□");
	}  

}
