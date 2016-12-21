// exam_swap_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void Swap(int tA, int tB);
void SwapWithPtr(int *tpA, int *tpB);


int main()
{
	int tA = 3;
	int tB = 2;


	//call by value
	printf("[original]\ttA : %d, tB : %d\n", tA, tB);
	Swap(tA, tB);
	printf("[original]\ttA : %d, tB : %d\n", tA, tB);

	printf("===ptr===\n");

	//call by pointer
	printf("[original]\ttA : %d, tB : %d\n", tA, tB);
	SwapWithPtr(&tA, &tB);
	printf("[original]\ttA : %d, tB : %d\n", tA, tB);


	int tInput = 0;
	cin >> tInput;

    return 0;

}



void Swap(int tA, int tB)
{
	int tTemp = 0;

	tTemp = tA;
	tA = tB;
	tB = tTemp;

	//표시
	printf("[in function]\ttA : %d, tB : %d\n", tA, tB);
}

//call by pointer로 매개변수를 넘김
void SwapWithPtr(int *tpA, int *tpB)
{

	int tTemp = 0;

	tTemp = *tpA;
	*tpA = *tpB;
	*tpB = tTemp;

	printf("[in function]\ttA : %d, tB : %d\n", *tpA, *tpB);

}


