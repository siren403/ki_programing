// exam_polymorphism.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Actor.h"
#include "Slime.h"
#include "BossSlime.h"


int main()
{
	CActor tActor;
	CSlime tSlime;
	CBossSlime tBossSlime;

	CUnit *tArray[3] = { NULL,NULL,NULL };
	tArray[0] = &tActor;
	tArray[1] = &tSlime;
	tArray[2] = &tBossSlime;

	for (int i = 0; i < 3; i++)
	{
		tArray[i]->Doit();

		tArray[i]->CUnit::Doit();
	}


    return 0;
}

