// exam_inheritance_02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fruit.h"

#include <iostream>

using namespace std;

int main()
{
	Fruit tFruit;

	tFruit.Print1();
	tFruit.Print2();
	tFruit.Print3();

	Food tFood;

	//int nA = tFood.price1;
	//int nB = tFood.price2;
	int nC = tFood.price3;
	cout << "price3 : " << nC << endl;

	int tInput = 0;
	cin >> tInput;


    return 0;
}

