#include "stdafx.h"
#include "Unit.h"
#include <iostream>

using namespace std;

CUnit::CUnit()
{
}


CUnit::~CUnit()
{
	cout << "[ENd]Unit" << endl;

}

void CUnit::Doit()
{
	cout << "CUnit" << endl;
}
