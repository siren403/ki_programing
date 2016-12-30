#pragma once
#include "Monster.h"

class CBossSlie :
	public CMonster
{
public:
	CBossSlie();
	~CBossSlie();

	virtual char DoBattle(CPlayer *tPlayer);

private:
	char CheckCompareCard(int tPlayerCard, int tSlimeCard);
	void DisplayCard(int tCardValue);

};

