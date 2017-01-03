#pragma once
#include "Bullet.h"

class CActor;

class CEnemyBullet :
	public CBullet
{
public:
	CEnemyBullet();
	virtual ~CEnemyBullet();

	virtual void Display(char *tpPixel) override;
	//virtual void Update() override;

	void SetPositionForFire(int tX, int tY);
	virtual bool DoCollisionWithActor(CActor *pPlayer);

};

