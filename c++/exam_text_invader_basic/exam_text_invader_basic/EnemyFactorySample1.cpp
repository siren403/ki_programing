#include "stdafx.h"
#include "EnemyFactorySample1.h"
//Enemys
#include "EnemyNormal.h"
//EnemyBullets
#include "EnemyBulletNormal.h"
#include "EnemyBulletPattern.h"

/*
좌우 이동 및 전진 패턴 
*/
CEnemyFactorySample1::CEnemyFactorySample1()
{
	mEnemys.reserve(5);

	CEnemy *tpEnemy = NULL;
	int tiEnemy = 0;
	int tiBullet = 0;

	for (tiEnemy = 0; tiEnemy < 10; tiEnemy++)
	{
		tpEnemy = new CEnemyNormal();
		tpEnemy->SetUp((WIDTH * 0.3f) + (3 * tiEnemy), 3);
		tpEnemy->SetSpeedPower(2.0f);
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

