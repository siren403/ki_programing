// exam_inheritrace_06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fruit.h"

int main()
{
	Food *pFood;
	Fruit myFruit;

	pFood = &myFruit;
	pFood->Print(100);

    return 0;
}

