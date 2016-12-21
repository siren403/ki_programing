// exam_array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

//임의의 인덱스를 매개변수로 받아서 그 인덱스에 해당하는 원소 값을 바꾸는 함수
void DoChangeElementWith(int tArray[],int tIndex,int tValue);

int main()
{

	int tArray[5] = { 0,0,0,0,0 };

	tArray[0] = 4;
	tArray[1] = 0;
	tArray[2] = 1;
	tArray[3] = 2;
	tArray[4] = 3;

	int ti = 0;

	for (ti = 0; ti < 5; ti++)
	{
		printf("%d\n", tArray[ti]);
	}


	//배열의 이름은 연속된 메모리 블럭의 시작 주소
	//tArray == &tArray[0]
	printf("%d\n", tArray);
	printf("%d\n", &tArray[0]);


	//[0]메모리 위치에서 5번째 위치의 메모리 주소
	//[0]주소 + (integer size * 5) = [5]의 주소
	printf("%d\n", &tArray[5]);
	printf("%d\n", &tArray[6]);


	//[0]메모리 위치에서 5번째 위치의 메모리에 초기화 되지 않은 값(쓰레기값)
	//배멸을 선언한다는건 지정한 개수의 메모리 블럭의 값들을 할당받아 초기화한다는 것
	printf("%d\n", tArray[5]);
	printf("%d\n", tArray[6]);


	DoChangeElementWith(tArray, 0, 100);
	printf("%d\n", tArray[0]);


	int tInput = 0;
	cin >> tInput;


    return 0;
}

void DoChangeElementWith(int tArray[], int tIndex, int tValue)
{
	tArray[tIndex] = tValue;
}


