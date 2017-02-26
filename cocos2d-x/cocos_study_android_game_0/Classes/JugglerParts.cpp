#include "JugglerParts.h"
#include "StopWatch.h"
#include "EasingFunc.h"
#include "Enemy.h"

#define PI 3.14159

#pragma region JuglerCircle

bool JugglerCircle::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("enemy/whitemask.png"));

	mIdleWatch = StopWatch::create();
	mIdleWatch->OnStart();
	this->addChild(mIdleWatch);
	mAttackWatch = StopWatch::create();
	mAttackWatch->OnStart();
	this->addChild(mAttackWatch);

	this->scheduleUpdate();
	return true;
}

void JugglerCircle::update(float dt)
{
	switch (mState)
	{
	case State::State_Idle:
		UpdateIdle(dt);
		break;
	case State::State_SeqAttack:
		UpdateAttack(dt);
		break;
	}
}
void JugglerCircle::UpdateIdle(float dt)
{
	mIdleWatch->OnUpdate(dt *  (0.5 * mRotateSpeedRatio));
	float delta = PI * mIdleWatch->GetAccTime();

	mIdlePosition.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	mIdlePosition.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	
	if (delta >= PI * 2)
	{
		mIdleWatch->OnReset();
	}

	this->setPosition(mIdlePosition);
}
void JugglerCircle::UpdateAttack(float dt)
{
	mAttackWatch->OnUpdate(dt);

	Vec2 pos;
	pos.x += EasingFunc::EaseExpoOut(sin(PI * (mAttackWatch->GetAccTime() / mAttackDuration)) * mAttackDuration, mAttackStartPos.x, mAttackTargetPos.x - mAttackStartPos.x, mAttackDuration);
	pos.y += EasingFunc::EaseExpoOut(sin(PI * (mAttackWatch->GetAccTime() / mAttackDuration)) * mAttackDuration, mAttackStartPos.y, mAttackTargetPos.y - mAttackStartPos.y, mAttackDuration);

	this->setPosition(pos);

	if (mAttackWatch->GetAccTime() >= mAttackDuration)
	{
		mAttackWatch->OnReset();
		this->setPosition(mIdlePosition);
		SetState(State::State_None);
	}
}

#pragma region set,get

void JugglerCircle::SetState(JugglerCircle::State state)
{
	mPrevState = mState;
	mState = state;
}

JugglerCircle::State JugglerCircle::GetState()
{
	return mState;
}

void JugglerCircle::SetRotateData(CircleRotateData data)
{
	mRotateData = data;
}

void JugglerCircle::SetRotateSpeedRatio(float ratio)
{
	mRotateSpeedRatio = ratio;
}

float JugglerCircle::GetRotateSpeedRatio()
{
	return mRotateSpeedRatio;
}

void JugglerCircle::SetCircleRadiusRatio(float ratio)
{
	mCircleRadiusRatio = ratio;
}

float JugglerCircle::GetCircleRadiusRatio()
{
	return mCircleRadiusRatio;
}


#pragma endregion

void JugglerCircle::OnAttack(Vec2 targetPos, float duration)
{
	mAttackStartPos = this->getPosition();

	//mAttackTargetPos =  ((targetPos - Vec2::ZERO).getNormalized() * 700);
	mAttackTargetPos = targetPos;

	mAttackDuration = duration == 0 ? 1 : duration;
	SetState(State::State_SeqAttack);
}

void JugglerCircle::Reposition()
{
	mRotateSpeedRatio = 1;
	mCircleRadiusRatio = 1;
	mIdleWatch->OnReset();
	mAttackWatch->OnReset();

	mIdlePosition.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount))
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	mIdlePosition.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount))
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);

	this->setPosition(mIdlePosition);
	mState = State::State_Idle;
}



#pragma endregion
