// exam_inheritace_04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fruit.h"
#include "Snack.h"

#include <iostream>

using namespace std;

int main()
{
	Food *pFood[2];
	Fruit myFruit;
	Snack mySnack;

	pFood[0] = &myFruit;
	pFood[1] = &mySnack;

	for (int i = 0; i <= 1; i++)
	{
		pFood[i]->SetPrice(100);
		//pFood[i]->SetPrice2(100);
	}

	mySnack.PrintOverride(1);
	mySnack.Food::PrintOverride(1);

	int tInput = 0;
	cin >> tInput;

    return 0;
}

