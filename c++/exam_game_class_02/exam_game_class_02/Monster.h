#pragma once
#include "Player.h"

class CMonster : public Character
{
protected:
	void DisplayGauge(int tCurrentValue, int tMaxValue);

public:
	CMonster();
	~CMonster();

	virtual char DoBattle(CPlayer *tPlayer) = 0;
};

