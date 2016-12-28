#pragma once
#include "Unit.h"
class CSlime :
	public CUnit
{
public:
	CSlime();
	~CSlime() override;

	void Doit() override;
};

