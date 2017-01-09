#pragma once
#include "EnemyBullet.h"
#include <vector>

using namespace std;

class CEnemyBulletPattern :
	public CEnemyBullet
{
private:
	vector<CEnemyBullet*> mBullets;
public:
	CEnemyBulletPattern();
	~CEnemyBulletPattern();

	virtual void Clean(char *tpPixel) override;
	virtual void Update() override;
	virtual void Display(char *tpPixel) override;

	virtual void Destroy() override;
	virtual void SetAlive(bool tIsAlive) override;
	virtual bool GetAlive() override;
	virtual void SetPositionForFire(int tX, int tY) override;
	virtual bool DoCollisionWithActor(CActor *pPlayer) override;

	CEnemyBulletPattern &AddBullet(CEnemyBullet *tpEnemyBullet);
};

