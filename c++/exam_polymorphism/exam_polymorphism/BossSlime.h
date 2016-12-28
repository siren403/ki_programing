#pragma once
#include "Unit.h"
class CBossSlime :
	public CUnit
{
public:
	CBossSlime();
	~CBossSlime() override;

	void Doit()	override;

};

