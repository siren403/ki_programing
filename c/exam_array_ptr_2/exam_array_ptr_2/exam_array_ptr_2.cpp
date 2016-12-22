// exam_array_ptr_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

#define WIDTH 3

int main()
{
	int tArray[2][3] = {
		{9,5,4},
		{1,3,8}
	};

	printf("%d\n", sizeof(tArray));
	printf("%d\n", sizeof(tArray[0]));
	printf("%d\n", sizeof(tArray[0][0]));



	int ti = 0;
	int tj = 0;
	//인덱스 접근 출력
	for (ti = 0; ti < 2; ti++)
	{
		for (tj = 0; tj < 3; tj++)
		{
			printf("i:%d, j:%d, value:%d\n", ti, tj, tArray[ti][tj]);
		}
		printf("=================\n");
	}

	//for1개로 배열출력
	for (int i = 0; i < 6; i++)
	{
		printf("address:%d, value:%d\n", tArray[0] + i, *(tArray[0] + i));

		printf("address:%d, value:%d\n", &tArray[0][0] + i, *(&tArray[0][0] + i));
	}
	printf("=================\n");

	int *tpPtr = NULL;
	int tCount = 2 * 3;

	tpPtr = &tArray[0][0];
	for (ti = 0; ti < tCount; ti++)
	{
		printf("address:%d, value:%d\n", tpPtr + ti, *(tpPtr + ti));
	}

	printf("=================\n");
	//포인터 변수를 사용,for문 2개
	//tpPtr = tArray[0];
	for (ti = 0; ti < 2; ti++)
	{
		for (tj = 0; tj < 3; tj++)
		{
			//printf("address:%d, value:%d\n", &(tpPtr + ti)[tj], (tpPtr + ti)[tj]);
			printf("%d\n", *(tpPtr + WIDTH * ti + tj));
		}
	}

	int tInput = 0;
	cin >> tInput;

    return 0;
}

