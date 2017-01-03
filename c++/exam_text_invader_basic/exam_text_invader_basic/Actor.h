#pragma once
#include "Unit.h"
#include "PlayerBullet.h"
#include "config.h"

class CEnemy;

class CActor :
	public CUnit
{
private:
	char mKey = 0;
	CPlayerBullet *mPlayerBullets = NULL;
	int mCurBulletIndex = 0;

public:
	CActor();
	virtual ~CActor();


	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;

	bool DoCollisionBulletWithEnemy(CEnemy *pEnemy);

	virtual void Destroy() override;

};

