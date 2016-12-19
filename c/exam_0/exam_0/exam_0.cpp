// exam_0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <time.h>
//#include <random>
#include <stdlib.h>

int main()
{

	srand(time(NULL));


	//printf("Hello World\n");

	//연산자
	/*
	int tA = 0;
	int tB = 0;

	tA = 3;
	tB = 2;

	float tResult = 0;

	tResult = tA + tB;
	printf("%f\n", tResult);


	tResult = tA - tB;
	printf("%f\n", tResult);


	tResult = tA * tB;
	printf("%f\n", tResult);


	tResult = (float)tA / tB;
	printf("%f\n", tResult);
	*/

	//반복문
	/*
	int ti = 0;
	int tj = 0;
	int tResult = 0;

	for (ti = 1; ti <= 9; ti++)
	{
		for (tj = 1; tj <= 9; tj++) 
		{
			tResult = ti * tj;

			printf("%d * %d", ti, tj);
			printf("= %d", tResult);
			printf("\n");
		
		}
	}
	*/


	//기본 미션
	int tInput = 0;
	int ti = 0;
	int tResult = 0;
	int tNum = 0;

	while (1)
	{

		printf("1 Captain America\n2 Iron Man\n9 Exit\n");
	
		scanf_s("%d", &tInput);


		switch (tInput)
		{
		case 1://cap * 5
			for (ti = 0; ti < 5; ti++)
			{
				printf("Call Captain America!!\n");
			}
			break;
		case 2://iron * 3
			for (ti = 0; ti < 3; ti++)
			{
				printf("Call Iron Man!!\n");
			}
			break;
		}

		tResult = rand() % 5 + 1;
		printf("%d\n",tResult);

		printf("숫자를 선택하세요.\n");
		scanf_s("%d", &tNum);
		if (tNum == tResult)
		{
			printf("맞았습니다.\n");
		}
		else
		{
			printf("틀렸습니다.\n");
		}

		if (9 == tInput)
		{
			printf("정말 종료하시겠습니까?(1/0) : ");

			scanf_s("%d", &tInput);
			if (1 == tInput)
			{
				break;
			}
		}
	}

	printf("==================\n");

	//int tInput = 0;
	//scanf_s("%d", &tInput);

    return 0;
}








