#ifndef __JUGGLERFINITESTATE_H__
#define __JUGGLERFINITESTATE_H__

#include "EnemyFiniteState.h"
#include "EasingFunc.h"
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

class StopWatch;

#pragma region None

class JugglerNoneState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerNoneState);
	virtual bool InitState() override;
	virtual ~JugglerNoneState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
};

#pragma endregion

#pragma region Idle

class JugglerIdleState : public EnemyFiniteState
{
private:
	StopWatch * mStopWatch = nullptr;
public:
	CREATE_STATE_FUNC(JugglerIdleState);
	virtual bool InitState() override;
	virtual ~JugglerIdleState();

protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
};

#pragma endregion

#pragma region SequenceAttack

class JugglerSeqAttackState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerSeqAttackState);
	virtual bool InitState() override;
	virtual ~JugglerSeqAttackState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	int mCurrentAttackIndex = 0;
	StopWatch * mStopWatch = nullptr;
};
#pragma endregion

#pragma region RushAttack

class JugglerRushAttackState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerRushAttackState);
	virtual bool InitState() override;
	virtual ~JugglerRushAttackState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	StopWatch * mStopWatch = nullptr;
	Vec2 mRushDirection;
	bool mIsCharging = false;
	float mChargeDuration = 0;
	float mChargeRotationRatio = 0;
	float mChargeRadiusRatio = 0;

	float mRushDuration = 0;
	float mRushRadiusRatio = 0;
	bool mIsRushReturn = false;

	EasingData mEaseChargeRotateData;
	EasingData mEaseOutRadiusData;
};

#pragma endregion

#pragma region CornerAttack

class JugglerCornerAttackState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerCornerAttackState);
	virtual bool InitState() override;
	virtual ~JugglerCornerAttackState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	Vec2 mCornerPostions[4];
	int mCornerIndex = 0;
	Vec2 mStartPosition;
	EasingData mMoveXEasingData;
	EasingData mMoveYEasingData;
	StopWatch * mStopWatch = nullptr;

	void InitMoveEasingData(EasingType type,Vec2 start,Vec2 end);

};

#pragma endregion

#pragma region VerticalAttack

class JugglerVerticalAttack : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerVerticalAttack);
	virtual bool InitState() override;
	virtual ~JugglerVerticalAttack();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	int mCircleCount = 0;
	vector<Vec2> mInitPositions;
	StopWatch * mStopWatch = nullptr;
	Size mMapSize;
};

#pragma endregion


#endif // !__JUGGLERFINITESTATE_H__
