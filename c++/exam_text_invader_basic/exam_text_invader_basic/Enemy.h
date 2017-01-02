#pragma once
#include "Character.h"
#include "EnemyBullet.h"
#define DIR_LEFT 0
#define DIR_RIGHT 1


class CEnemy :
	public CCharacter
{
protected:
	CEnemyBullet *mEnemyBullets = NULL;
	int mCurBulletIndex = 0;

	unsigned int mDelay = 0;
	unsigned int mTemp = 0;

public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;
	
	void SetPlayer(CPlayer *tPlayer);
	bool DoCollisionBulletWithActor(CPlayer *pPlayer);
};

