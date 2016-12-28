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

void Food::Print(int n)
{
	cout << "parent print : " << n << endl;
}
