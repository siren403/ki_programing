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

	auto sprite = this->SetSprite(Sprite::create("enemy/circle.png"));
	sprite->getTexture()->setAliasTexParameters();
	
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
	float delta = PI * mIdleWatch->GetAccTime();
	mIdleWatch->OnUpdate(dt);
	mIdlePosition.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * mRotateData.circleRadius;
	mIdlePosition.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * mRotateData.circleRadius;
	if (delta >= PI * 2)
	{
		mIdleWatch->OnReset();
	}

	switch (mState)
	{
	case State::State_Idle:
		UpdateIdle(dt);
		break;
	case State::State_Attack:
		UpdateAttack(dt);
		break;
	}
}
void JugglerCircle::UpdateIdle(float dt)
{
	mIdlePosition = ccpLerp(this->getPosition(), mIdlePosition, dt);
	this->setPosition(mIdlePosition);
}
void JugglerCircle::UpdateAttack(float dt)
{
	mAttackWatch->OnUpdate(dt);

	Vec2 pos;
	pos += EasingFunc::EaseSinInOut(sin((PI / mAttackDuration) * mAttackWatch->GetAccTime()) * mAttackDuration, mAttackStartPos, mAttackTargetPos - mAttackStartPos, mAttackDuration);
	this->setPosition(pos);

	if (mAttackWatch->GetAccTime() >= mAttackDuration)
	{
		mAttackWatch->OnReset();
		mState = State::State_Idle;
	}
}

void JugglerCircle::SetState(JugglerCircle::State state)
{
	mState = state;
}

void JugglerCircle::SetRotateData(CircleRotateData data)
{
	mRotateData = data;
}

void JugglerCircle::OnAttack(Vec2 targetPos, float duration)
{

	mAttackStartPos = this->getPosition();
	mAttackTargetPos = targetPos;
	mAttackDuration = duration == 0 ? 1 : duration;
	mState = State::State_Attack;
}



#pragma endregion
