#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Actor.h"
#include "EnemyParts.h"

using namespace cocos2d;


class Enemy : public Actor
{
protected:
	Vector<EnemyParts *> mParts;
public:
	CREATE_FUNC(Enemy);
	virtual bool init() override;

	void AddParts(EnemyParts * tParts);
	// bool checkCollisionBulletToParts(CBullet * tBullet);
	//void CheckCollisionToActor(Actor * tActor);

	//getter, setter
	virtual void SetAlive(bool tIsAlive) override;
	virtual bool IsAlive() override;
	virtual bool GetPartsAlive();

	void DestroyParts();
	void CheckCollisionActor(Actor * actor);
};

#endif // !__CENEMY_H__
