#include "stdafx.h"
#include "EnemyBulletNormal.h"


CEnemyBulletNormal::CEnemyBulletNormal()
{
}


CEnemyBulletNormal::~CEnemyBulletNormal()
{
}

void CEnemyBulletNormal::Update()
{
	if (mIsAlive)
	{
		mY = mY + 1;
	}
}

bool CEnemyBulletNormal::DoCollisionWithActor(CActor * pPlayer)
{
	return CEnemyBullet::DoCollisionWithActor(pPlayer);
}
