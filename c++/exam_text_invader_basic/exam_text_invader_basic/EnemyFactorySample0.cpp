#include "stdafx.h"
#include "EnemyFactorySample0.h"
#include "Enemy.h"

CEnemyFactorySample0::CEnemyFactorySample0()
{
	CEnemy * tpEnemy = NULL;

	tpEnemy = new CEnemy();
	tpEnemy->SetUp(WIDTH / 2, 0);
	mEnemys.push_back(tpEnemy);

}


CEnemyFactorySample0::~CEnemyFactorySample0()
{
}
