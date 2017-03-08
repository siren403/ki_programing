#include "JugglerParts.h"
#include "StopWatch.h"
#include "EasingFunc.h"
#include "Enemy.h"

#define PI 3.14159f

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
	mIdleWatch->OnUpdate(dt *  (0.5f * mRotateSpeedRatio));
	float delta = PI * mIdleWatch->GetAccTime();

	mIdlePosition.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	mIdlePosition.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	
	mIdlePosition += mOffset;

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
	pos.x += EasingFunc::EaseQuintOut(sin(PI * (mAttackWatch->GetAccTime() / mAttackDuration)) * mAttackDuration, mAttackStartPos.x, mAttackTargetPos.x - mAttackStartPos.x, mAttackDuration);
	pos.y += EasingFunc::EaseQuintOut(sin(PI * (mAttackWatch->GetAccTime() / mAttackDuration)) * mAttackDuration, mAttackStartPos.y, mAttackTargetPos.y - mAttackStartPos.y, mAttackDuration);

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

CircleRotateData JugglerCircle::GetRotateData()
{
	return mRotateData;
}

void JugglerCircle::SetOffset(Vec2 offset)
{
	mOffset = offset;
}

void JugglerCircle::StartAnimation()
{
	/*GetSprite()->runAction(RepeatForever::create(Sequence::create(
		DelayTime::create(mRotateData.circleIndex * 0.02f),
		Spawn::create(
			ScaleBy::create(0.18f,1.15f, 0),
			ScaleBy::create(0.18f, 0, 0.85f),
			nullptr),
			ScaleTo::create(0.18f, 1),
		nullptr)));*/
	/*GetSprite()->runAction(RepeatForever::create(Sequence::create(
		DelayTime::create(mRotateData.circleIndex * 0.05f),
		EaseSineIn::create( ScaleTo::create(0.16f, 1.1f, 0.7)),
		EaseSineOut::create(ScaleBy::create(0.16f, 0.9, 1.25f)),
		EaseSineInOut::create(ScaleTo::create(0.16f, 1)),
		nullptr)));*/
	GetSprite()->runAction(RepeatForever::create(
		RotateBy::create(0.6f + 0.5f * random(0.0f,1.0f), Vec3(0, 0, 360))
	));

	/*GetSprite()->runAction(RepeatForever::create(Sequence::create(
		DelayTime::create(mRotateData.circleIndex * 0.01),
		RotateBy::create(0.25,Vec3(0,180,0)),
		RotateBy::create(0.25, Vec3(0, -180, 0)),
		nullptr)
	));*/
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
