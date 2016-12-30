// exam_fsm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

typedef int(*tpFunc)(int, int);

int DoAddictive(int tA, int tB);
int DoSubtract(int tA, int tB);

int main()
{
	int tState = 0;





	tpFunc tFuncArray[2] = { DoAddictive,DoSubtract };

	tState = 0;
	tFuncArray[tState](3, 2);

	tState = 1;
	tFuncArray[tState](3, 2);

    return 0;
}

int DoAddictive(int tA, int tB)
{
	int tResult = 0;

	tResult = tA + tB;

	cout << "add : " << tResult << endl;

	return tResult;
}

int DoSubtract(int tA, int tB)
{
	int tResult = 0;

	tResult = tA - tB;

	cout << "subtract : " << tResult << endl;

	return tResult;
}