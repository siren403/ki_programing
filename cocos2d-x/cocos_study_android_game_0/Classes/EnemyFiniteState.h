#ifndef __ENEMYFINITESTATE_H__
#define __ENEMYFINITYSTATE_H__

#include "cocos2d.h"

class Enemy;

#define CREATE_STATE_FUNC(__TYPE__) \
static __TYPE__* Create(Enemy * entity) \
{ \
	__TYPE__ * state = new __TYPE__();\
	state->mEntity = entity;\
	if(state->InitState())\
	{ \
		return state;\
	} \
	return nullptr;\
}

using namespace cocos2d;


class EnemyFiniteState
{
	friend Enemy;
protected:
	Enemy * mEntity = nullptr;

	template<class T>
	T * GetEntity()
	{
		return (T*)mEntity;
	}

	virtual void OnEnter();
	virtual void OnUpdate(float dt);
	virtual void OnExit();
public:
	CREATE_STATE_FUNC(EnemyFiniteState);
	virtual bool InitState();
	virtual ~EnemyFiniteState();
};

#endif // !__ENEMYFINITYSTATE_H__
