// exam_template_function_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


//int GetMax(int a, int b);
//double GetMax(double ta, double tb);

template<class T1, class T2>
T2 GetMax(T1 a, T1 b);

int main()
{
	int n1 = 1;
	int n2 = 3;
	int result = 0;
	double r1 = 1.5;
	double r2 = 3.5;
	double result2 = 0;

	result = GetMax<int, double>(n1, n2);
	result2 = GetMax<double, int>(r1, r2);

	cout << "test1 : " << endl;
	cout << result << endl;
	cout << result2 << endl;

	cin >> result;

	return 0;
}

//int GetMax(int a, int b)
//{
//	int buf;
//
//	if (a > b)
//		buf = a;
//	else
//		buf = b;
//
//	return buf;
//}
//
//double GetMax(double ta, double tb)
//{
//	double tBuf;
//
//	if (ta > tb)
//	{
//		tBuf = ta;
//	}
//	else
//	{
//		tBuf = tb;
//	}
//
//	return tBuf;
//}

//template<class T>
//T GetMax(T a, T b)
//{
//	T buf;
//
//	if (a > b)
//	{
//		buf = a;
//	}
//	else
//	{
//		buf = b;
//	}
//
//	return buf;
//}

template<class T1, class T2>
T2 GetMax(T1 a, T1 b)
{
	T2 buf;

	if (a > b)
	{
		buf = (T2)a;
	}
	else
	{
		buf = (T2)b;
	}

	return buf;
}
