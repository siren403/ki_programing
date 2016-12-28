#pragma once
#include "Monster.h"

class CSlime :
	public CMonster
{
public:
	CSlime();
	~CSlime();

	virtual char DoBattle(CPlayer *tPlayer);
};

