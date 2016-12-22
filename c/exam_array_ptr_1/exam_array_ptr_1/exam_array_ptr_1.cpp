// exam_array_ptr_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void DoChangeElementWith(int tArray[], int tIndex, int tValue);
void DoChangeElementWithPtr(int *tArray, int tIndex, int tValue);

void DisplyArray(int tArray[], int tLength);


int main()
{

	int tArray[5] = { 0,0,0,0,0 };

	tArray[0] = 4;
	tArray[1] = 0;
	tArray[2] = 1;
	tArray[3] = 2;
	tArray[4] = 3;

	DisplyArray(tArray, 5);

	DoChangeElementWith(tArray, 0, 777);
	DisplyArray(tArray, 5);

	DoChangeElementWithPtr(tArray, 0, 444);
	DisplyArray(tArray, 5);

	int tInput = 0;
	cin >> tInput;

    return 0;
}


void DoChangeElementWith(int tArray[], int tIndex, int tValue) 
{
	tArray[tIndex] = tValue;
}
void DoChangeElementWithPtr(int *tArray, int tIndex, int tValue)
{
	*(tArray + tIndex) = tValue;
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