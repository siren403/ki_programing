#ifndef __BOSSFINITESTATE_H__
#define __BOSSFINITESTATE_H__

#include "EnemyFiniteState.h"

class Boss;
class BossHand;
class BossHead;

class BossIdleState : public EnemyFiniteState
{
private:
	BossHand * mLHand = nullptr;
	BossHand * mRHand = nullptr;
	float mLHandRadian = 0;
	float mRHandRadian = 0;

	BossHead * mHead = nullptr;
	Action * mHeadAction = nullptr;

	void HandIdleMotion(BossHand * hand, float & radian, float dt);

	float mCurrentTime = 0;

protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
public:
	CREATE_STATE_FUNC(BossIdleState);
	virtual bool InitState() override;
	virtual ~BossIdleState();

};


class BossHandAttackState : public EnemyFiniteState
{
private:
	BossHand * mLHand = nullptr;
	BossHand * mRHand = nullptr;

	float mAttackDelay = 0;
	float mCurrentTime = 0;
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
public:
	CREATE_STATE_FUNC(BossHandAttackState);
	virtual bool InitState() override;
	virtual ~BossHandAttackState();
};

#endif // !__BOSSFINITESTATE_H__
