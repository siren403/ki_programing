#ifndef __JUGGLERPARTS_H__
#define __JUGGLERPARTS_H__

#include "EnemyParts.h"

class StopWatch;

#pragma region JugglerCircle

struct CircleRotateData
{
	int circleIndex = 0;
	int circleCount = 0;
	float circleRadius = 0;
	float circlePivot = 0;

	CircleRotateData() {}
	CircleRotateData(int index,int count,float radius,float pivot) :
		circleIndex(index),circleCount(count),circleRadius(radius),circlePivot(pivot)
	{
	}
};

class JugglerCircle : public EnemyParts
{
public:
	enum State
	{
		State_None = 0,
		State_Idle = 1,
		State_SeqAttack = 2,
	};
private:
	JugglerCircle::State mPrevState;
	JugglerCircle::State mState;
	CircleRotateData mRotateData;
	//idle 상태시 회전속도값의 대한 비율
	float mRotateSpeedRatio = 1;
	//idle 상태시 회전반지름의 대한 비율
	float mCircleRadiusRatio = 1;

	StopWatch * mIdleWatch = nullptr;
	StopWatch * mAttackWatch = nullptr;
	
	Vec2 mIdlePosition;
	Vec2 mOffset;

	//attack
	float mAttackDuration = 0;
	Vec2 mAttackStartPos;
	Vec2 mAttackTargetPos;

	void UpdateIdle(float dt);
	void UpdateAttack(float dt);
public:
	CREATE_FUNC(JugglerCircle);
	virtual bool init() override;
	virtual void update(float dt) override;

	//get,set
	void SetState(JugglerCircle::State state);
	JugglerCircle::State GetState();
	void SetRotateData(CircleRotateData data);
	void SetRotateSpeedRatio(float ratio);
	float GetRotateSpeedRatio();
	void SetCircleRadiusRatio(float ratio);
	float GetCircleRadiusRatio();
	CircleRotateData GetRotateData();
	void SetOffset(Vec2 offset);

	void StartAnimation();

	void OnAttack(Vec2 targetPos, float duration);
	void Reposition();
};

#pragma endregion



#endif // !__JUGGLERPARTS_H__
