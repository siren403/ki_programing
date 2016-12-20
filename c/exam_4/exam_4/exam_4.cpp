// exam_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
/*
가위바위보

하나의 main.cpp
변수와 함수이름 주의
난수 이용
승패조건비교 switch
함수 이용

가위 0
바위 1
보 2

*/

int DoAlphaGoAction();
int CheckWinner(int tPlayer, int tAlphaGo);
void ShowAction(int tAction);

int main()
{
	srand(time(NULL));
	
	int tPlayer = 0;
	int tAlphaGo = 0;
	int tWinner = 0;

	while (1)
	{
		printf("1. Play\n2. Exit\n");

		scanf_s("%d", &tPlayer);

		if (1 == tPlayer)
		{
			do
			{
				printf("가위,바위,보를 선택해 주세요.\n");
				printf("0:가위\t1:바위\t보:2\n");
				scanf_s("%d", &tPlayer);

			} while (0 > tPlayer || 3 <= tPlayer);//가위,바위,보 이외는 재입력


			tAlphaGo = DoAlphaGoAction();


			printf("===플레이어===\n");
			ShowAction(tPlayer);
			printf("===알파고===\n");
			ShowAction(tAlphaGo);


			tWinner = CheckWinner(tPlayer, tAlphaGo);

			switch (tWinner)
			{
			case 0:
				printf("\n비겼습니다.\n");
				break;
			case 1:
				printf("\n이겼습니다.\n");
				break;
			case 2:
				printf("\n졌습니다.\n");
				break;
			}

		
		}
		else if (2 == tPlayer)
		{
			break;
		}

	}

    return 0;
}


int DoAlphaGoAction()
{
	int tResult = 0;

	tResult = rand() % 3 + 0;

	return tResult;
}

//가위,바위,보 텍스트 출력
void ShowAction(int tAction)
{
	switch (tAction)
	{
	case 0:
		printf("가위\n");
		break;
	case 1:
		printf("바위\n");
		break;
	case 2:
		printf("보\n");
		break;
	}
}


/*
승자 판정

Return:
	1 Player Win
	0 Draw
	-1 AlphaGo Win
*/
int CheckWinner(int tPlayer, int tAlphaGo) 
{
	int tWinner = 0;

	int tResult = tPlayer - tAlphaGo;

	switch (tResult)
	{
	case 0:
		tWinner = 0;
		break;
	case 1:
		tWinner = 1;
		break;
	case -2:
		tWinner = 1;
		break;
	case -1:
		tWinner = -1;
		break;
	case 2:
		tWinner = -1;
		break;
	}
	
	return tWinner;
}

