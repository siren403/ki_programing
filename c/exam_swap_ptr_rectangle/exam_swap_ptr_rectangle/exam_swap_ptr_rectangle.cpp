// exam_swap_ptr_rectangle.cpp : Defines the entry point for the console application.
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

struct Sample
{
	char tCharA = 0;
	char tCharB = 0;
	int tInteger = 0;
};

void SwapRectangleWithPtr(SRectangle *tpARectangle,SRectangle *tpBRectangle);
int DoCalculateArea(SRectangle *tpRectangle);

void DisplayRectangle(SRectangle *tpRectangle);

int main()
{
	Sample tSample;

	printf("%d\n", sizeof(tSample));




	SRectangle tRectArray[5];

	printf("%d\n", &tRectArray);
	printf("%d\n", &tRectArray[0]);
	printf("%d\n", &tRectArray[0].mLeft);


	SRectangle tARectangle;
	tARectangle.mLeft = 0;
	tARectangle.mRight = 5;
	tARectangle.mTop = 0;
	tARectangle.mBottom = 5;

	SRectangle tBRectangle;
	tBRectangle.mLeft = 0;
	tBRectangle.mRight = 3;
	tBRectangle.mTop = 0;
	tBRectangle.mBottom = 3;

	/*
	printf("%d\n", sizeof(tARectangle));
	printf("%d\n", &tARectangle);
	printf("%d", &tARectangle + 1);

	printf("%d\n%d\n", &tARectangle.mLeft, &tARectangle.mRight);
	printf("%d\n%d\n", &tARectangle.mTop, &tARectangle.mBottom);
*/
	


	//tARectangle넓이 구하는 함수
	tARectangle.mArea = DoCalculateArea(&tARectangle);
	//tBRectangle넓이 구하는 함수
	tBRectangle.mArea = DoCalculateArea(&tBRectangle);

	printf("===tARectArea\n");
	DisplayRectangle(&tARectangle);
	printf("===tBRectArea\n");
	DisplayRectangle(&tBRectangle);
	printf("\n\n");


	//Swap
	SwapRectangleWithPtr(&tARectangle, &tBRectangle);

	printf("===tARectArea\n");
	DisplayRectangle(&tARectangle);
	printf("===tBRectArea\n");
	DisplayRectangle(&tBRectangle);

	int tInput = 0;
	cin >> tInput;

    return 0;
}

void SwapRectangleWithPtr(SRectangle *tpARectangle, SRectangle *tpBRectangle)
{
	SRectangle tTemp;

	tTemp = *tpARectangle;
	*tpARectangle = *tpBRectangle;
	*tpBRectangle = tTemp;
}

int DoCalculateArea(SRectangle *tpRectangle)
{
	int tArea = 0;

	int tWidth = 0;
	int tHeight = 0;

	tWidth = tpRectangle->mRight - tpRectangle->mLeft;
	tHeight = tpRectangle->mBottom - tpRectangle->mTop;

	tArea = tWidth * tHeight;

	return tArea;
}

void DisplayRectangle(SRectangle *tpRectangle)
{
	printf("mLeft:%d, mRight:%d, mTop:%d, mBottom:%d\ntArea:%d\n",
		(*tpRectangle).mLeft, (*tpRectangle).mRight, 
		(*tpRectangle).mTop, (*tpRectangle).mBottom,
		(*tpRectangle).mArea);
}

