// exam_iostream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


namespace my1
{
	int BoxVolume(int length, int width = 1, int height = 1);

	void SimpleFunc(void)
	{
		std::cout << "BestCom이 정의한 함수" << std::endl;
	}
	
	int BoxVolume(int length, int width, int height)
	{
		return length*width*height;
	}
}

namespace my2
{
	void SimpleFunc(void)
	{
		std::cout << "ProgCom이 정의한 함수" << std::endl;
	}
}

void Ref(int &a);
void Ref(int &a)
{
	a++;
}

int main()
{
	cout << "Hello World" << endl;


	my1::SimpleFunc();
	my2::SimpleFunc();


	cout << my1::BoxVolume(3,3,3)<<endl;
	cout << my1::BoxVolume(5,5)<<endl;
	cout << my1::BoxVolume(7)<<endl;

	int tA = 10;
	int &rA = tA;

	cout << tA << endl;
	Ref(tA);
	cout << tA << endl;
	rA++;
	cout << tA << endl;

	cout << &tA << endl;
	cout << &rA << endl;


	int tInput = 0;
	cin >> tInput;


    return 0;
}


