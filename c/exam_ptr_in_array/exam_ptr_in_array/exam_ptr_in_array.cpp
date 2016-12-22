// exam_ptr_in_array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct SRectangle
{
	int mLeft = 0;
	int mRight = 0;
	int mTop = 0;
	int mBottom = 0;

	int mArea = 0;
};


void SwapRectangleElement(SRectangle *tRectArray[], int tIndexA, int tIndexB);
void DisplayRectangle(SRectangle *tRectangle);

int main()
{

	//int *tArray[5] = { NULL,NULL,NULL,NULL,NULL };

	//int tA = 1;
	//int tB = 2;
	//int tC = 3;
	//int tD = 4;
	//int tE = 5;
	//
	//int ti = 0;

	////tA~tB까지의 변수들의 주소를 tArray에 각 원소들에 담아보세요
	//tArray[0] = &tA;
	//tArray[1] = &tB;
	//tArray[2] = &tC;
	//tArray[3] = &tD;
	//tArray[4] = &tE;


	//for (ti = 0; ti < 5; ti++)
	//{
	//	printf("%d\n", *tArray[ti]);
	//}


	SRectangle *tRectArray[2] = { NULL,NULL };

	//두원소를 Swap하는 프로그램을 만드세요
	SRectangle tRectA;
	SRectangle tRectB;
	
	tRectA.mLeft = 0;
	tRectA.mRight = 5;
	tRectA.mTop = 0;
	tRectA.mBottom = 5;

	tRectB.mLeft = 0;
	tRectB.mRight = 10;
	tRectB.mTop = 0;
	tRectB.mBottom = 10;

	tRectArray[0] = &tRectA;
	tRectArray[1] = &tRectB;

	printf("[RectA]\n");
	DisplayRectangle(tRectArray[0]);
	printf("[RectB]\n");
	DisplayRectangle(tRectArray[1]);

	SwapRectangleElement(tRectArray, 0, 1);

	printf("=============\n");

	printf("[RectA]\n");
	DisplayRectangle(tRectArray[0]);
	printf("[RectB]\n");
	DisplayRectangle(tRectArray[1]);


	int tInput = 0;
	cin >> tInput;

    return 0;
}


void SwapRectangleElement(SRectangle *tRectArray[], int tIndexA, int tIndexB)
{
	SRectangle tTemp;

	tTemp = *tRectArray[tIndexA];
	*tRectArray[tIndexA] = *tRectArray[tIndexB];
	*tRectArray[tIndexB] = tTemp;
}

void DisplayRectangle(SRectangle *tRectangle)
{
	printf("mLeft:%d, mRight:%d, mTop:%d, mBottom:%d, mArea:%d\n",
		tRectangle->mLeft,
		tRectangle->mRight,
		tRectangle->mTop,
		tRectangle->mBottom,
		tRectangle->mArea
		);

}

