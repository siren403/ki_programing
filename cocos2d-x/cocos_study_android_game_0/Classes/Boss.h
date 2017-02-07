#ifndef __BOSS_H__
#define __BOSS_H__

#include "cocos2d.h"
#include "Enemy.h"

class Boss : public Enemy
{
public:
	CREATE_FUNC(Boss);
	virtual bool init() override;
	virtual void update(float dt) override;

};

#endif // !__BOSS_H__
