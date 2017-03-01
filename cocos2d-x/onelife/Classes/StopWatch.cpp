#include "StopWatch.h"

bool StopWatch::init()
{
	if (!Node::init())
	{
		return false;
	}

	mCurrentTime = 0;
	mState = StopWatch::State::Stop;

	return true;
}

void StopWatch::update(float dt)
{
	this->OnUpdate(dt);
}

void StopWatch::SetAutoUpdate(bool isUpdate)
{
	if (isUpdate)
	{
		this->scheduleUpdate();
	}
	else
	{
		this->unscheduleUpdate();
	}
}

float StopWatch::GetAccTime()
{
	return mCurrentTime;
}



void StopWatch::OnStart(float initTime)
{
	if (mState == StopWatch::State::Stop)
	{
		mCurrentTime = initTime;
	}
	mState = StopWatch::State::Play;
}

void StopWatch::OnUpdate(float dt)
{
	if (mState == StopWatch::State::Play)
	{
		mCurrentTime += dt;
	}
}

float StopWatch::OnStop()
{
	float result = mCurrentTime;
	OnReset();
	mState = StopWatch::State::Stop;
	return result;
}

float StopWatch::OnPause()
{
	mState = StopWatch::State::Pause;
	return mCurrentTime;
}

void StopWatch::OnReset()
{
	mCurrentTime = 0;
}

