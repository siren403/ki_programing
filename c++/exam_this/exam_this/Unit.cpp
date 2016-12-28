#include "stdafx.h"
#include "Unit.h"

#include <iostream>

using namespace std;

CUnit::CUnit()
{
	(*this).mX = 0;
	(*this).mHP = 0;
}


CUnit::~CUnit()
{
}


void CUnit::DisplayStatus()
{
	cout << "mX : " << this->mX << endl;
	cout << "mHp : " << this->mHP << endl;


}
