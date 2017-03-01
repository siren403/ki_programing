#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

using namespace cocos2d;

enum ActorType
{
	Actor_None = 0,
	Actor_Player = 1,
	Actor_Arrow = 2,
	Actor_EnemyParts = 3,
	Actor_Tile = 4,
};

class Actor : public Node
{
protected:
	bool mIsAlive = true;
	ActorType mType = ActorType::Actor_None;
public:
	CREATE_FUNC(Actor);
	virtual bool init() override;

	virtual bool IsAlive();
	virtual void SetAlive(bool tIsAlive);
	virtual void OnCollisionOther(bool isCollision, Node * other, Vec2 normal = Vec2::ZERO);

	ActorType GetActorType();
};

#endif // !__ACTOR_H__
