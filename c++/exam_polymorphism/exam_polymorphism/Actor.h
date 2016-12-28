#pragma once
#include "Unit.h"
class CActor :
	public CUnit
{
public:
	CActor();
	~CActor() override;

	void Doit() override;
};

