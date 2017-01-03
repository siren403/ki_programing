#pragma once
#include "EnemyBullet.h"
class CEnemyBulletNormal :
	public CEnemyBullet
{
public:
	CEnemyBulletNormal();
	~CEnemyBulletNormal();

	virtual void Update() override;
	virtual bool DoCollisionWithActor(CActor *pPlayer) override;
};

