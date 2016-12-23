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
	
	srand(time(NULL));//랜덤 시드 지정

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
					printf("\t");
					printf("[ 일반 슬라임이 나타났다. ]");
					printf("\n\n");
					tSlime = tNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ 보스 슬라임이 나타났다. ]");
					printf("\n\n");
					tSlime = tBossSlime;
				}

				printf("1.싸움을 건다!!");
				printf("\n");
				printf("2.도망친다..");
				printf("\n");
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
						printf("\n\n\t\t");
						printf("[ 용사는 죽었다... ]");
						printf("\n\n\n");

						tGameState = QUIT;
					}

					printf("Input Any Key");
					printf("\n");
					cin >> tInput;
				}
				else if (tInput == 2)
				{
					printf("\t");
					printf("[ 용사는 도망쳤다... ]");
					printf("\n");

					PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
				}
			}
			else//적과 마주치지 않음
			{
				if (tPlayer->mPosition != MAP_LENGTH - 1)//맵 끝에 도달하지 않았으면
				{
					printf("\t");
					printf("[ 어떻게 할까? ]");
					printf("\n\n");
					printf("1.전진하기");
					printf("\n");
					printf("2.돌아가기");
					printf("\n");


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
					printf("\t");
					printf("[ 게임을 클리어하였습니다. ]");
					printf("\n\n");
					printf("Input Any Key");
					printf("\n");

					cin >> tInput;
					tGameState = QUIT;
				}
			}

			break;
		case QUIT://종료
			printf("\n\n\n");
			printf("계속하시겠습니까?(y/n): ");
			cin >> tIsContinue;
			if (YES == tIsContinue)
			{
				tGameState = 0;
			}
			break;
		}
		system("cls");
	}

	//각 동적할당 변수들 초기화
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

//타이틀 화면을 그리고 
//시작,종료를 입력받는다.
int DisplayTitle()
{
	int tInput = 0;

	printf("\n\n\t");
	printf("[ 용사는 일차원 ]");
	printf("\n\n\n");

	printf("1.게임 시작");
	printf("\n");
	printf("2.종료");
	printf("\n");

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

//플레이어의 위치정보를 변경하고
//맵의 위치 정보를 갱신한다.
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

		printf("\t");
		printf("[ 이동 할 수 없다... ]");
		printf("\n");
		printf("Input Any Key");
		printf("\n");
		cin >> tInput;
	}

}

//현재의 맵 상태를 그린다.
void DrawMap(int tMap[])
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n");
	printf("==");
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

//플레이어가 적을 마주보고 있는지 검사한다.
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

//Power값으로 대상의 Health값을 감소 시킨다
//음수 방지로 -1이하는 0으로 고정시킨다
void DoAttack(int tPower, int *tTargetCurrentHealth) 
{
	*tTargetCurrentHealth -= tPower;
	if (*tTargetCurrentHealth < 0)
	{
		*tTargetCurrentHealth = 0;
	}
}

//일반 슬라임의 전투 방식
//주사위 게임
char DoNormalBattle(Player *tPlayer, Slime *tSlime)
{
	int tInput = 0;
	int tDiceNumber = 0;

	char tResult = 0;

	printf("\t\t");
	printf("[주사위 배틀]");
	printf("\n\t");
	printf("눈금이 4이상이면 용사가 공격!");
	printf("\n\t");
	printf("눈금이 3이하면 슬라임이 공격한다.");
	printf("\n\n");

	while (1)
	{
		printf("\t");
		printf("[용사]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[슬라임]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("1. 주사위를 던진다.");
		printf("\n");
		cin >> tInput;

		printf("================================================");
		printf("\n\n");
		tDiceNumber = DoThrowDice(6);

		printf("\n\t   ");
		printf("주사위 -> ");
		DisplayGauge(tDiceNumber, 6);
		printf("\n\n");

		if (4 <= tDiceNumber)//4이상 승리
		{
			printf("\t");
			printf("공격!!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.", tPlayer->mPower);
			printf("\n\n");

			DoAttack(tPlayer->mPower,&tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t");
				printf("[ 슬라임을 잡았다!! ]");
				printf("\n\n");

				if (DoThrowDice(3) <= 3)
				{
					printf("\t\t");
					printf("[ 용사가 강해졌다. ]");
					printf("\n\n");
					tPlayer->mHealth += 2;
					tPlayer->mPower += 2;
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDiceNumber)//3이하 패배
		{
			printf("\t");
			printf("슬라임이 %d만큼 피해를 입혔다.", tSlime->mPower);
			printf("\n\n");

			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

//주사위를 던져 눈금을 리턴한다.
int DoThrowDice(int tMaxNumber)
{
	int tResult = 0;

	tResult = rand() % tMaxNumber + 1;

	return tResult;
}

//보스슬라임의 전투 방식
//가위,바위,보
char DoBossBattle(Player *tPlayer, Slime *tSlime)
{
	int tPlayerCard = 0;
	int tSlimeCard = 0;
	int tCompareResult = 0;

	char tResult = 0;

	printf("\n\t\t");
	printf("[ 가위,바위,보 게임 ]");
	printf("\n\n\t");
	printf("가위,바위,보를 내서 이긴쪽이 공격한다!");
	printf("\n\n\n");

	while (1)
	{
		printf("[용사]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[보스 슬라임]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("[1]:가위, [2]:바위, [3]:보");
		printf("\n\n");
		printf("선택하세요 : ");
		cin >> tPlayerCard;
		printf("\n");
		printf("================================================");
		printf("\n");


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
			printf("\t\t\t");
			printf("비겼습니다.");
			printf("\n\n");

		}
		else if (1 == tCompareResult)//승리
		{
			printf("\t");
			printf("승리!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.", tPlayer->mPower);
			printf("\n\n");

			DoAttack(tPlayer->mPower, &tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t");
				printf("[ 슬라임을 잡았다!! ]");
				printf("\n\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//패배
		{
			printf("\t");
			printf("패배...");
			printf("보스 슬라임이 %d만큼 피해를 입혔다.", tSlime->mPower);
			printf("\n\n");

			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

//플레이어와 슬라임의 패를 비교하여 결과를 리턴한다.
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
//각 값에 맞는 텍스트를 출력한다.
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

//현재값과 최대값을 입력받아 게이지는 출력한다.
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
