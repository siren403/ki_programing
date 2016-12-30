#pragma once
#include "Unit.h"
class CActor : public CUnit
{
public:
	CActor();
	~CActor();

protected:
	virtual void DoIdle() override;
	virtual void DoAttack() override;

};

