#pragma once
#include "Bullet.h"
class CEnemyBulletLt :
	public CBullet
{
public:
	CEnemyBulletLt();
	~CEnemyBulletLt();

	virtual void Update() override;
};

