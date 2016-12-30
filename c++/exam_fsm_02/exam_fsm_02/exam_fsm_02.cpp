// exam_fsm_02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class CUnit
{
	enum { STATE_IDLE = 0, STATE_ATTACK = 1 };

private:
	int mState = 0;

protected:
	void DoIdle();
	void DoAttack();

public:
	void SetState(int tState);
	void Execute();
};

int main()
{
	CUnit *tpUnit = NULL;
	tpUnit = new CUnit();

	tpUnit->SetState(0);
	tpUnit->Execute();

	tpUnit->SetState(1);
	tpUnit->Execute();

	if (NULL != tpUnit)
	{
		delete tpUnit;
		tpUnit = NULL;
	}

	int tInput = 0;
	cin >> tInput;

    return 0;
}

void CUnit::DoIdle()
{
	cout << "DoIdle" << endl;
}
void CUnit::DoAttack()
{
	cout << "DoAttack" << endl;
}
void CUnit::SetState(int tState)
{
	mState = tState;
}

void CUnit::Execute()
{
	switch (mState)
	{
	case STATE_IDLE:
	{
		DoIdle();
	}
	break;
	case STATE_ATTACK:
	{
		DoAttack();
	}
	break;
	}
}

