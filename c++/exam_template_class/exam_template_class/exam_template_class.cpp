// exam_template_class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template<class T> 
class Rectangle
{
private:
	T mLeft = 0;
	T mTop = 0;
	T mWidth = 0;
	T mHeight = 0;
public:
	Rectangle(T n1, T n2, T n3, T n4);
	~Rectangle();

	T GetRight();
	T GetBottom();
};

int main()
{
	Rectangle<int> tRectInt(50, 50, 100, 100);
	cout << tRectInt.GetRight() << endl;

	Rectangle<double> tRectDouble(50.5, 50.5, 100.1, 100.5);
	cout << tRectDouble.GetRight() << endl;

	int tInput = 0;
	cin >> tInput;


    return 0;
}

template<class T>
Rectangle<T>::Rectangle(T n1, T n2, T n3, T n4)
{
	mLeft = n1;
	mTop = n2;
	mWidth = n3;
	mHeight = n4;
}

template<class T>
Rectangle<T>::~Rectangle()
{
}

template<class T>
T Rectangle<T>::GetRight()
{
	return mLeft + mWidth;
}

template<class T>
T Rectangle<T>::GetBottom()
{
	return mTop + mHeight;
}
