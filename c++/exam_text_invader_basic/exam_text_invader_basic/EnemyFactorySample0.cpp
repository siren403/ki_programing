#include "stdafx.h"
#include "EnemyFactorySample0.h"
#include "Enemy.h"
#include "EnemyBulletNormal.h"

CEnemyFactorySample0::CEnemyFactorySample0()
{
	CEnemy * tpEnemy = NULL;

	tpEnemy = new CEnemy();
	tpEnemy->SetUp(WIDTH / 2, 0);

	//CEnemyBulletNormal * tpEnemyBulletNormal = NULL;
	//tpEnemyBulletNormal = new CEnemyBulletNormal();
	//tpEnemyBulletNormal->SetDirectionAndSpeedPower(0, 1, 2);
	//tpEnemy->AddBullet(tpEnemyBulletNormal);

	mEnemys.push_back(tpEnemy);

}


CEnemyFactorySample0::~CEnemyFactorySample0()
{
}
