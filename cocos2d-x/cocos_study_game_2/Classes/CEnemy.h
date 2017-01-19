#ifndef __CENEMY_H__
#define __CENEMY_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CEnemyParts.h"

using namespace cocos2d;

class CBullet;
class CActor;

class CEnemy : public CUnit
{
protected:
	Vector<CEnemyParts *> mParts;
	int mCurrentState = 0;
	int mDestroyPartsCount = 0;
public:
	CREATE_FUNC(CEnemy);
	virtual bool init() override;

	void addParts(CEnemyParts * tParts);
	bool checkCollisionBulletToParts(CBullet * tBullet);
	void checkCollisionToActor(CActor * tActor);
	
	virtual bool getPartsAlive();

	virtual void setIsAlive(bool tIsAlive) override;
	virtual bool getIsAlive() override;
	void setState(int state);
	enum 
	{
		STATE_IDLE = 0,
		STATE_ATTACK = 1,
	};

	void DestroyParts();
};

#endif // !__CENEMY_H__
