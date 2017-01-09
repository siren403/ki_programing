#pragma once
#include "Actor.h"
#include "EnemyBullet.h"
#include "Timer.h"
#include <vector>


using namespace std;

class CEnemy :
	public CUnit
{
protected:

	vector<CEnemyBullet*> mEnemyBullets;
	int mCurBulletIndex = 0;

	CTimer mTimer;

	virtual void Shot();
public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;
	virtual void Destroy() override;
	
	bool DoCollisionBulletWithActor(CActor *pPlayer);

	void AddBullet(CEnemyBullet *tpEnemyBullet);
	void SetBulletInterval(unsigned int tInterval);

};

