#include "stdafx.h"
#include "Food.h"

#include <iostream>

using namespace std;

Food::Food()
{
}


Food::~Food()
{
}

void Food::SetPrice(int myprice)
{
	this->price = myprice;
	cout << "Food : " << myprice << endl;
}

void Food::PrintOverride(int t)
{
	cout << "부모 클래스" << t << endl;
}
