// exam_this.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Unit.h"

#include <iostream>

using namespace std;

int main()
{
	CUnit tUnit;

	tUnit.DisplayStatus();

	int tInput = 0;
	cin >> tInput;

    return 0;
}

