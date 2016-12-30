#pragma once

#include "Player.h"
#include "Slime.h"
#include "BossSlime.h"


class CCharacterFactory
{
private:
	typedef Character*(CCharacterFactory::*Creater)(void);
	Creater mCreater[3];
	int mState = 0;
public:
	CCharacterFactory();
	~CCharacterFactory();

	enum
	{
		STATE_PLAYER = 0,
		STATE_SLIME = 1,
		STATE_BOSS_SLIME = 2,
	};

	void SetState(int tState);
	Character* Execute();

	Character* CreatePlayer();
	Character* CreateSlime();
	Character* CreateBossSlime();

};


