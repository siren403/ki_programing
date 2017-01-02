#pragma once
#include "Character.h"
#include "PlayerBullet.h"
#include "gamesettings.h"

class CEnemy;

class CPlayer :
	public CCharacter
{
private:
	char mKey = 0;
	CPlayerBullet *mPlayerBullets = NULL;
	int mCurBulletIndex = 0;

public:
	CPlayer();
	virtual ~CPlayer();


	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;

	bool DoCollisionBulletWithEnemy(CEnemy *pEnemy);

};

