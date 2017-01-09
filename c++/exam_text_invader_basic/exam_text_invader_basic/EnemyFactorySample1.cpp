#include "stdafx.h"
#include "EnemyFactorySample1.h"

//Enemys
#include "EnemyNormal.h"

//EnemyBullets
#include "EnemyBulletNormal.h"
#include "EnemyBulletPattern.h"

#define ENEMY_MOVE_WIDTH 16
#define ENEMY_LEFT_START_X (WIDTH * 0.2f)
#define ENEMY_RIGHT_START_X (WIDTH * 0.6f)


CEnemyFactorySample1::CEnemyFactorySample1()
{
	mEnemys.reserve(5);

	CEnemyNormal *tpEnemy = NULL;
	int tiEnemy = 0;
	int tiBullet = 0;

	for (tiEnemy = 0; tiEnemy < 5; tiEnemy++)
	{
		tpEnemy = new CEnemyNormal();
		tpEnemy->SetUp(ENEMY_LEFT_START_X + (3 * tiEnemy), 3);
		tpEnemy->SetDirectionAndSpeedPower(1, 1, 2.0f);
		tpEnemy->SetMoveWidth(ENEMY_MOVE_WIDTH);
		tpEnemy->SetBulletInterval(200);

		//일직선 10개 발사
		for (tiBullet = 0; tiBullet < 5; tiBullet++)
		{
			tpEnemy->AddBullet(new CEnemyBulletNormal(0, 1, 3));
		}
		mEnemys.push_back(tpEnemy);
	}
	
	for (tiEnemy = 0; tiEnemy < 5; tiEnemy++)
	{
		tpEnemy = new CEnemyNormal();
		tpEnemy->SetUp(ENEMY_RIGHT_START_X + (3 * tiEnemy), 2);
		tpEnemy->SetDirectionAndSpeedPower(-1, 1, 2.0f);
		tpEnemy->SetMoveWidth(ENEMY_MOVE_WIDTH);
		tpEnemy->SetBulletInterval(200);

		//일직선 10개 발사
		for (tiBullet = 0; tiBullet < 5; tiBullet++)
		{
			tpEnemy->AddBullet(new CEnemyBulletNormal(0, 1, 3));
		}
		mEnemys.push_back(tpEnemy);
	}
}


CEnemyFactorySample1::~CEnemyFactorySample1()
{
}

