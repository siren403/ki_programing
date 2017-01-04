#pragma once
#include "Enemy.h"

#include <vector>

using namespace std;

class CGameManager;

class CEnemyFactory
{
protected:
	vector<CEnemy*> mEnemys;
public:
	CEnemyFactory();
	~CEnemyFactory();

	virtual void DoSetting(CGameManager & tGameManager);

	void Destroy();
};

