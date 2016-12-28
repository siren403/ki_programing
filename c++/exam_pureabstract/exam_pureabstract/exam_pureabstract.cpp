// exam_pureabstract.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fruit.h"
#include "Fish.h"

int main()
{
	Fruit tFruit;
	tFruit.Print(5);

	Fish tFish;
	tFish.Print(5);

	Food *tFood = &tFruit;
	tFood->Print(10);

    return 0;
}

