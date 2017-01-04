#pragma once
#include "Bullet.h"
#include <DirectXMath.h>

class CEnemy;

class CActorBullet :
	public CBullet
{
public:
	CActorBullet();
	virtual ~CActorBullet();

	//virtual void Display(char *tpPixel) override;
	virtual void Update() override;

	bool DoCollisionWithEnemy(CEnemy *pEnemy);
};

