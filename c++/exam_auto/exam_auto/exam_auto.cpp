// exam_auto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{

	float tF = 0.0f;
	auto tG = 0.0f;

	int tA = 0;
	tA = 7;
	cout << tA << endl;


	auto tB = 0;
	cout << tB << endl;


	int *tC = NULL;
	tC = new int();

	*tC = 77;
	cout << *tC << endl;

	if (NULL != tC)
	{
		delete tC;
		tC = NULL;
	}

	auto tpPtr = new int();

	*tpPtr = 777;
	cout << *tpPtr << endl;

	if (NULL != tpPtr)
	{
		delete tpPtr;
		tpPtr = NULL;
	}

	int tInput = 0;
	cin >> tInput;

    return 0;
}

