#include "stdafx.h"
#include "Snack.h"

#include <iostream>

using namespace std;

Snack::Snack()
{
}


Snack::~Snack()
{
}

void Snack::SetPrice2()
{
	cout << "Snack : " << endl;
}

void Snack::PrintOverride(int t)
{
	Food::PrintOverride(t);
	cout << "자식 클래스" << t + 1 << endl;
}
