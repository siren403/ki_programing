// exam_inheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Food.h"
#include "Fruit.h"


#include <iostream>

using namespace std;

int main()
{
	Fruit tFruit;

	tFruit.print();

	tFruit.print2();

	int tInput = 0;
	cin >> tInput;

    return 0;
}

