#pragma once
#include "Actor.h"
#include "EnemyBullet.h"
#include <vector>
#define DIR_LEFT 0
#define DIR_RIGHT 1

using namespace std;

class CEnemy :
	public CUnit
{
protected:
	//vector<vector<CEnemyBullet*>*> mBullets;

	vector<CEnemyBullet*> mEnemyBullets;
	int mCurBulletIndex = 0;

	unsigned int mDelay = 0;
	unsigned int mTemp = 0;

public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Display(char *tpPixel) override;
	virtual void Update() override;
	virtual void Clean(char *tpPixel) override;
	virtual void Destroy() override;
	
	bool DoCollisionBulletWithActor(CActor *pPlayer);

	void AddBullet(CEnemyBullet *tpEnemyBullet);

};

