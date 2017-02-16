#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Actor.h"
#include "EnemyParts.h"
#include <map>

using namespace cocos2d;
using namespace std;

class EnemyFiniteState;

typedef map<int, EnemyFiniteState *> EnemyFSMap;
typedef Map<int, EnemyParts *> EnemyPartsMap;

class Enemy : public Actor
{
private:
	EnemyFSMap mFiniteState;
	bool mIsScheduleUpdate = false;

protected:
	EnemyPartsMap mParts;
	EnemyPartsMap::iterator mMapPartItor;
	EnemyParts * mLifeParts = nullptr;


	//FiniteState
	EnemyFiniteState * mCurrentFiniteState = nullptr;
	void AddState(int key, EnemyFiniteState * state);
	void ChangeState(int key);
	EnemyFiniteState * GetState(int state);
public:
	CREATE_FUNC(Enemy);
	virtual bool init() override;
	virtual void update(float dt) override;

	virtual void OnActivate(bool isActive);

	//getter, setter
	virtual void SetAlive(bool tIsAlive) override;
	virtual bool IsAlive() override;
	
	//EnemyParts
	void AddParts(int key, EnemyParts * tParts,bool isLifeParts = false, int localZOrder = 0);
	EnemyParts * GetParts(int key);
	void DestroyParts();
	void CheckCollisionActor(Actor * actor);

	virtual ~Enemy();
};

#endif // !__CENEMY_H__

