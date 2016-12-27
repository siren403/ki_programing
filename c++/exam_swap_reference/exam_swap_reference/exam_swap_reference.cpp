// exam_swap_reference.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void SwapWithRef(int &tA, int &tB);



int main()
{
	int tA = 10;
	int tB = 99;

	cout << "tA : " << tA << endl << "tB : " << tB << endl;

	cout << "tA address : " << &tA << endl;
	SwapWithRef(tA, tB);
	
	cout << "tA : " << tA << endl << "tB : " << tB << endl;


	cin >> tA;

    return 0;
}

void SwapWithRef(int &tA, int &tB)
{
	cout << "SwapWithRef" << endl;
	cout << "[Swap] tA address : " << &tA << endl;


	int tTemp = 0;

	tTemp = tA;
	tA = tB;
	tB = tTemp;

}


