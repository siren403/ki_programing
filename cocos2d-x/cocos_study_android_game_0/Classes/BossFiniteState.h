#ifndef __BOSSFINITESTATE_H__
#define __BOSSFINITESTATE_H__

#include "EnemyFiniteState.h"

class Boss;
class BossHand;
class BossHead;

#pragma region Idle

class BossIdleState : public EnemyFiniteState
{
private:

	float mCurrentTime = 0;
	bool mIsActive = false;
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
public:
	CREATE_STATE_FUNC(BossIdleState);
	virtual bool InitState() override;
	virtual ~BossIdleState();


	void SetActive(bool isActive);
};
#pragma endregion

#pragma region HandAttack

class BossHandAttackState : public EnemyFiniteState
{
private:
	BossHand * mLHand = nullptr;
	BossHand * mRHand = nullptr;

	float mCurrentTime = 0;
	bool mIsSecondAttack = false;

	void HandAttacKLockOn(BossHand * hand);
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
public:
	CREATE_STATE_FUNC(BossHandAttackState);
	virtual bool InitState() override;
	virtual ~BossHandAttackState();
};
#pragma endregion



#endif // !__BOSSFINITESTATE_H__
