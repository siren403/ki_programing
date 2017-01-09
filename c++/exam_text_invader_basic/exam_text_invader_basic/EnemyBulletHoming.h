#pragma once
#include "EnemyBullet.h"
#include "Actor.h"
class CEnemyBulletHoming :
	public CEnemyBullet
{
private:
	CActor *mPlayer = NULL;

public:
	CEnemyBulletHoming();
	~CEnemyBulletHoming();

	virtual void Update() override;
	CEnemyBulletHoming * SetTarget(CActor *tpPlayer);

};

