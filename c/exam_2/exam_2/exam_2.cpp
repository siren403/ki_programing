// exam_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//함수 선언
void Swap(int tA, int tB);

int main()
{
	int tA = 3;
	int tB = 2;

	Swap(tA, tB);

	printf("tA : %d, tB : %d\n", tA, tB);

    return 0;
}

//함수 정의
void Swap(int tA, int tB)
{

	int tTemp = 0;

	tTemp = tA;
	tA = tB;
	tB = tTemp;

	printf("Swap\ntA : %d, tB : %d\n",tA, tB);
}

