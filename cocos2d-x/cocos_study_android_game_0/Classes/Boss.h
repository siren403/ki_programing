#ifndef __BOSS_H__
#define __BOSS_H__

#include "cocos2d.h"
#include "Enemy.h"

class BossIdleState;
class BossHandAttackState;

class Boss : public Enemy
{
	friend BossIdleState;
	friend BossHandAttackState;
private:
	enum State
	{
		State_None = 0,
		State_Idle = 1,
		State_HandAttack = 2,
	};
	enum Parts
	{
		Parts_None = 0,
		Parts_Body = 1,
		Parts_Head = 2,
		Parts_LHand = 3,
		Parts_RHand = 4,
	};

public:
	CREATE_FUNC(Boss);
	virtual bool init() override;

	virtual void OnActivate(bool isActive) override;
};

#endif // !__BOSS_H__
