#pragma once
#include "Unit.h"
#include "ActorBullet.h"
#include "config.h"
#include <vector>

using namespace std;

class CEnemy;

class CActor :
	public CUnit
{
private:
	char mKey = 0;
	
	vector<CActorBullet*> mActorBullets;
	int mCurBulletIndex = 0;

public:
	CActor();
	virtual ~CActor();


	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;
	virtual void Destroy() override;

	bool DoCollisionBulletWithEnemy(CEnemy *pEnemy);
	void AddBullet(CActorBullet *tpActorBullet);

};

