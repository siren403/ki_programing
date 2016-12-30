#include "stdafx.h"
#include "Unit.h"

#include <iostream>

using namespace std;

CUnit::CUnit()
{
}

CUnit::~CUnit()
{
}

void CUnit::DoIdle()
{
	cout << "[Unit] Idle" << endl;
}

void CUnit::DoAttack()
{
	cout << "[Unit] Attack" << endl;
}

void CUnit::SetState(int tState)
{
	mState = tState;
}

void CUnit::Execute()
{
	(this->*mArray[mState])();

}
