// exam_overload.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void MyFunc(void);
void MyFunc(char c);
void MyFunc(int a, int b);



int main()
{
	MyFunc();
	MyFunc('a');
	MyFunc(10,10);

	int tInput = 0;
	cin >> tInput;

    return 0;
}


void MyFunc(void)
{
	cout << "My Func(void)" << endl;
}
void MyFunc(char c)
{
	cout << "My Func(char c) called" << endl;
}
void MyFunc(int a,int b)
{
	cout << "My Func(int a,int b) called" << endl;
}
