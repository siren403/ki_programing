#ifndef __BOSSHAND_H__
#define __BOSSHAND_H__

#include "EnemyParts.h"


class BossHand : public EnemyParts
{
public:
	enum HandDir
	{
		HandDir_Left = -1,
		HandDir_Right = 1,
	};
	enum State
	{
		Idle = 0,
		Attack = 1,
	};
private:
	char mHandDir = 0;
	
	Vec2 mInitPos;
	
	BossHand::State mState;
	
	//idle
	float mIdleRadian = 0;

	//attack
	Vec2 mAttackTargetPos;


	void UpdateIdle(float dt);
	void UpdateAttack(float dt);
public:
	CREATE_FUNC(BossHand);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;

	void InitHand(HandDir dir);

	void OnAttack(Vec2 localPos);
};

#endif // !__BOSSHAND_H__
