#include "StopWatch.h"

bool StopWatch::init()
{
	if (!Node::init())
	{
		return false;
	}

	mCurrentTime = 0;
	mState = StopWatch::State::Stop;

	this->scheduleUpdate();
	return true;
}

void StopWatch::update(float dt)
{
	if (mState == StopWatch::State::Play)
	{
		mCurrentTime += dt;
	}
}

void StopWatch::OnStart()
{
	if (mState == StopWatch::State::Stop)
	{
		mCurrentTime = 0;
	}
	/*else if (mState == StopWatch::State::Pause)
	{

	}*/
	mState = StopWatch::State::Play;
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

