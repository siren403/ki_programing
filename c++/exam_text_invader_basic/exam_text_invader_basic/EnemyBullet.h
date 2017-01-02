#pragma once
#include "Bullet.h"

class CPlayer;

class CEnemyBullet :
	public CBullet
{
protected:
	CPlayer *mPlayer = NULL;
public:
	CEnemyBullet();
	virtual ~CEnemyBullet();

	//virtual void Update() override;
	virtual void Update();

	void SetTarget(CPlayer *tpPlayer);
	void SetPositionForFire(int tX, int tY);
	bool DoCollisionWithActor(CPlayer *pPlayer);
};

