// exam_dice.cpp : Defines the entry point for the console application.
//

//사용자 정의 헤더 파일
#include "stdafx.h"

//표준 헤더 파일
#include <stdlib.h>
#include <time.h>

int DoRollDice(int tMin,int tMax);
void ShowDiceResult(int tDiceNumber);

int main()
{
	srand(time(NULL));

	int tDiceNumber = 0;
	int tDiceSide = 0;
	int tIsContinue = 0;

	printf("주사위의 면의 개수 : ");
	scanf_s("%d", &tDiceSide);

	while (1)
	{

		/*printf("주사위의 면의 개수(0:종료) : ");
		scanf_s("%d", &tDiceSide);
		
		if (0 == tDiceSide)
		{
			break;
		}*/

		printf("주사위를 던질까요?(1/0)\t");
		scanf_s("%d", &tIsContinue);


		if (0 == tIsContinue)
		{
			break;
		}
		
		
		tDiceNumber = DoRollDice(1, tDiceSide);

		printf("%d", tDiceNumber);
		printf("\n");

		ShowDiceResult(tDiceNumber);

	}


    return 0;
}

void ShowDiceResult(int tDiceNumber)
{
	//함수로 만들어서 작동하게 만드세요
	switch (tDiceNumber)
	{
	case 1:
	case 2:
	case 3:
		printf("you lose\n");
		break;
	default:
		printf("you win\n");
		break;
	}

	//판단, 3이하 패,4이상 승
	/*
	if (tDiceNumber <= 3)
	{
	printf("you lose\n");
	}
	else// if(tDiceNumber >= 4)
	{
	printf("you win\n");
	}
	*/

}


int DoRollDice(int tMin, int tMax)
{
	int tResult = 0;

	tResult = rand() % tMax + tMin;

	return tResult;
}

