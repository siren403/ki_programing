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

	bool mIsFollow = false;
protected:
	EnemyPartsMap mParts;
	EnemyPartsMap::iterator mPartMapItor;
	EnemyParts * mLifeParts = nullptr;
	unsigned int mDeathCount = 0;

	//FiniteState
	EnemyFiniteState * mCurrentFiniteState = nullptr;
	void AddState(int key, EnemyFiniteState * state);
	
public:
	CREATE_FUNC(Enemy);
	virtual bool init() override;
	virtual void update(float dt) override;

	//Enemy의 활성화 상태에 따른 개별 처리 시 사용
	//ex) false전달 시 Idle상태에서 상태 전이 x 
	virtual void OnActivate(bool isActive);

	//getter, setter
	virtual void SetAlive(bool tIsAlive) override;
	virtual bool IsAlive() override;
	
	void SetCameraFollow(bool isFollow);
	bool IsCameraFollow();
	unsigned int GetDeathCount();

	//EnemyParts
	void AddParts(int key, EnemyParts * tParts,bool isLifeParts = false, int localZOrder = 0);
	EnemyParts * GetParts(int key);
	EnemyPartsMap * GetPartsMap();
	void DestroyParts();
	void CheckCollisionActor(Actor * actor);

	//State
	void ChangeState(int key);
	EnemyFiniteState * GetState(int state);
	

	virtual ~Enemy();
};

#endif // !__CENEMY_H__

