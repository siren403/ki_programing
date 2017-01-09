// exam_recursive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int FactorialWithRecursive(int tN);
int FactorialNoRecursive(int tN);

int main()
{

	int tTestNumber = 0;
	int tResult = 0;



	tResult = FactorialWithRecursive(tTestNumber);

	cout << "FactorialWithRecursive: " << tResult << endl;



	tResult = FactorialNoRecursive(tTestNumber);

	cout << "FactorialNoRecursive: " << tResult << endl;



	int tInput = 0;
	cin >> tInput;


    return 0;
}

int FactorialWithRecursive(int tN)
{
	if (0 == tN)
	{
		return 1;
	}
	else
	{
		return tN * FactorialWithRecursive(tN - 1);
	}
}

int FactorialNoRecursive(int tN)
{
	int tResult = 0;

	int ti = 0;
	int tTemp = 0;

	if (0 == tN)
	{
		tResult = 1;
	}
	else
	{
		tTemp = 1;

		for (ti = tN; ti > 0; ti--)
		{
			tTemp = tTemp * ti;
		}
		tResult = tTemp;
	}
	return tResult;
}
