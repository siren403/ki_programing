#include "JugglerParts.h"
#include "StopWatch.h"

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
	
	mStopWatch = StopWatch::create();
	mStopWatch->OnStart();
	this->addChild(mStopWatch);

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
	}
}
void JugglerCircle::UpdateIdle(float dt)
{
	mStopWatch->OnUpdate(dt * 0.4);
	float delta = PI * mStopWatch->GetAccTime();
	
	Vec2 pos;
	pos.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * mRotateData.circleRadius;
	pos.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * mRotateData.circleRadius;
	this->setPosition(pos);

	if (delta >= PI * 2)
	{
		mStopWatch->OnReset();
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



#pragma endregion
