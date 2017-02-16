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
	};
private:
	JugglerCircle::State mState;
	CircleRotateData mRotateData;
	StopWatch * mStopWatch = nullptr;

	void UpdateIdle(float dt);
public:
	CREATE_FUNC(JugglerCircle);
	virtual bool init() override;

	virtual void update(float dt) override;

	void SetState(JugglerCircle::State state);
	void SetRotateData(CircleRotateData data);
};

#pragma endregion



#endif // !__JUGGLERPARTS_H__
