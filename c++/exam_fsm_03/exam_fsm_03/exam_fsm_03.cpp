// exam_fsm_03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Unit.h"
#include "Actor.h"
#include <iostream>



int main()
{


	CUnit *tpUnitArray[2] = { NULL,NULL };

	tpUnitArray[0] = new CUnit();
	tpUnitArray[1] = new CActor();

	int ti = 0;

	for (ti = 0; ti < 2; ti++)
	{
		tpUnitArray[ti]->SetState(CUnit::STATE_IDLE);
		tpUnitArray[ti]->Execute();
	}

	for (ti = 0; ti < 2; ti++)
	{
		tpUnitArray[ti]->SetState(CUnit::STATE_ATTACK);
		tpUnitArray[ti]->Execute();
	}


	for (ti = 0; ti < 2; ti++)
	{
		if (tpUnitArray[ti] != NULL)
		{
			delete tpUnitArray[ti];
			tpUnitArray[ti] = NULL;
		}
	}

	/*tpUnit->SetState(CUnit::STATE_IDLE);
	tpUnit->Execute();

	tpUnit->SetState(CUnit::STATE_ATTACK);
	tpUnit->Execute();

	if (NULL != tpUnit)
	{
		delete tpUnit;
		tpUnit = NULL;
	}*/


	int tInput = 0;
	std::cin >> tInput;

    return 0;
}

