#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

using namespace cocos2d;

class Actor : public Node
{
protected:
	bool mIsAlive = true;
public:
	CREATE_FUNC(Actor);
	virtual bool init() override;


	virtual bool GetIsAlive();
	virtual void SetIsAlive(bool tIsAlive);
};

#endif // !__ACTOR_H__
