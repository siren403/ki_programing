// exam_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

/*
난수 맞추기

하나의 main.cpp
변수와 함수 이름 주의
난수 이용
게임루프 사용
기회는 10번
같은지 큰지 작은지
다음의 함수 작성



*/
int DoThinkAlphago(int tFrom, int tTo);
int DoCheckInputNumber();
char IsContinue();
void ShowHint(int tPlayer,int tAlphago,int tMaxNumber);


void EvaluateWithRetryCount(int tCount);

int main()
{
	srand(time(NULL));

	int tPlayer = 0;
	int tAlphago = 0;
	char tIsContinue = 'y';

	int tAlphagoMaximumNumber = 10;
	int tPlayerLimitCount = 10;

	int tCurrentCount = 0;

	while ('y' == tIsContinue)
	{
		printf("숫자 예측을 시작합니다.\n");
		tCurrentCount = tPlayerLimitCount;
		tAlphago = DoThinkAlphago(0, tAlphagoMaximumNumber);

		while (1)
		{
			printf("숫자를 입력하세요 : ");
			tPlayer = DoCheckInputNumber();

			if (tPlayer == tAlphago)
			{
				printf("정답입니다!!\n");
				break;
			}
			else
			{
				//틀림 카운트 감소
				tCurrentCount--;
			
				if (0 < tCurrentCount)
				{
					ShowHint(tPlayer, tAlphago, tAlphagoMaximumNumber);
				}
				else
				{
					printf("예측에 실패하였습니다.\n");
					break;
				}

			}
		}

		tIsContinue = IsContinue();
	}
    return 0;
}

void ShowHint(int tPlayer, int tAlphago, int tMaxNumber)
{
	//힌트
	if (tPlayer > tAlphago)
	{
		printf("알파고보다 큽니다.\n");
	}
	else if (tPlayer < tAlphago)
	{
		printf("알파고보다 작습니다.\n");
	}
}


int DoThinkAlphago(int tFrom, int tTo)
{
	int tResult = 0;

	tResult = rand() % (tTo + 1) + tFrom;

	return tResult;
}
int DoCheckInputNumber()
{
	int tInput = 0;

	scanf_s("%d", &tInput);

	return tInput;
}
char IsContinue()
{
	char tInput = 'a';

	while (1)
	{
		printf("계속 하실려요?(y/n)?");
		scanf_s("%c", &tInput);
		scanf_s("%c", &tInput);

		if ('y' == tInput || 'n' == tInput)
		{
			break;
		}
		else
		{
			printf("입력 에러, y와 n중에서 선택하세요\n");
		}

	}

	return tInput;
}
void EvaluateWithRetryCount(int tCount)
{

}