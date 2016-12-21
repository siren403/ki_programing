// exam_array_ptr_0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void DisplyArray(int tArray[], int tLength);
void DoChangeElementWith(int *tArray, int tIndex, int tValue);

int main()
{


	int tArray[5] = { 0,0,0,0,0 };
	tArray[0] = 4;
	tArray[1] = 0;
	tArray[2] = 1;
	tArray[3] = 2;
	tArray[4] = 3;


	DisplyArray(tArray, 5);

	//포인터의 증감연산
	int *tpPtr = NULL;
	tpPtr = &tArray[0];

	int ti = 0;
	for (ti = 0; ti < 5; ti++)
	{
		*(tpPtr + ti) = ti + 1;
		//*(tArray + ti) = ti + 1;
	}

	DisplyArray(tArray, 5);


	printf("%d\n", tArray[1]);
	printf("%d\n", *(tpPtr + 1));

	DoChangeElementWith(tArray, 1, 99);

	DisplyArray(tArray, 5);


    return 0;
}

void DisplyArray(int tArray[], int tLength)
{
	int ti = 0;

	printf("[ ");
	for (ti = 0; ti < tLength; ti++)
	{
		printf("(%d):%d", ti, tArray[ti]);
		if (ti < tLength - 1)
		{
			printf(", ");
		}
	}
	printf(" ]\n\n");
}


void DoChangeElementWith(int *tArray, int tIndex, int tValue)
{
	*(tArray + tIndex) = tValue;
}
