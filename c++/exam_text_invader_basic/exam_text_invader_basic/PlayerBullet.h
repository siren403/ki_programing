#pragma once
#include "Bullet.h"
#include <DirectXMath.h>

class CEnemy;

class CPlayerBullet :
	public CBullet
{
public:
	CPlayerBullet();
	virtual ~CPlayerBullet();

	//virtual void Display(char *tpPixel) override;
	virtual void Update() override;

	bool DoCollisionWithEnemy(CEnemy *pEnemy);
};

