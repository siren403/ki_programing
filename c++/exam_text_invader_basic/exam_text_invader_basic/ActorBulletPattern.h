#pragma once
#include "ActorBullet.h"
#include <vector>

using namespace std;

class CActorBulletPattern :
	public CActorBullet
{
private:
	vector<CActorBullet*> mBullets;
public:
	CActorBulletPattern();
	~CActorBulletPattern();

	virtual void Clean(char *tpPixel) override;
	virtual void Update() override;
	virtual void Display(char *tpPixel) override;

	virtual void Destroy() override;
	virtual void SetAlive(bool tIsAlive) override;
	virtual bool GetAlive() override;
	virtual void SetPositionForFire(int tX, int tY) override;
	virtual bool DoCollisionWithEnemy(CEnemy *tpEnemy) override;

	CActorBulletPattern &AddBullet(CActorBullet *tpEnemyBullet);

};

