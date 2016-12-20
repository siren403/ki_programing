// exam_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//함수 선언
float DoAddictive(float tA, float tB);

float DOMinus(float tA, float tB);
float DOMultiply(float tA, float tB);
float DODivide(float tA, float tB);

int main()
{

	//연산자
	float tA = 0;
	float tB = 0;

	tA = 3;
	tB = 2;

	float tResult = 0;

	//tResult = tA + tB;
	tResult = DoAddictive(tA, tB);
	printf("%f\n", tResult);


	tResult = DOMinus(tA, tB);
	printf("%f\n", tResult);


	tResult = DOMultiply(tA, tB);
	printf("%f\n", tResult);


	tResult = DODivide(tA, tB);
	printf("%f\n", tResult);


    return 0;
}

//함수 정의
float DoAddictive(float tA, float tB)
{
	float tResult = 0.0f;

	tResult = tA + tB;

	return tResult;
}

float DOSubtract(float tA, float tB) 
{
	float tResult = 0.0f;

	tResult = tA - tB;

	return tResult;
}
float DOMultiply(float tA, float tB)
{
	float tResult = 0.0f;

	tResult = tA * tB;

	return tResult;
}
float DODivide(float tA, float tB)
{
	float tResult = 0.0f;

	tResult = tA / tB;

	return tResult;
}
