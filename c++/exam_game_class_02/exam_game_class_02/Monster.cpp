#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::DisplayGauge(int tCurrentValue, int tMaxValue)
{
	int ti = 0;

	for (ti = 0; ti < tCurrentValue; ti++)
	{
		printf("бс");
	}
	for (ti = 0; ti < tMaxValue - tCurrentValue; ti++)
	{
		printf("бр");
	}
}