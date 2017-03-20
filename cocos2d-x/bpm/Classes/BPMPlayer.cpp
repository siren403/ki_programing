#include "BPMPlayer.h"

void BPMPlayer::update(float dt)
{
	if (mIsUpdate)

	{
		mCurrentTime += dt;

		if (mCurrentTime != 0 && mCurrentTime >= mBeatTime)
		{
			mCurrentTempo++;

			if (mCallBackBPM != nullptr)
			{
				mCallBackBPM(mCurrentTempo);
			}

			if (mCurrentTempo >= mTempo)
			{
				mCurrentTempo = 0;
			}
			mCurrentTime = 0.0f;
		}
	}
}

bool BPMPlayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	mIsUpdate = false;

	return true;
}

void BPMPlayer::SetCallBackBPM(CallBackBPM callBack)
{
	mCallBackBPM = std::move(callBack);
}

void BPMPlayer::SetBPM(int bpm)
{
	mBPM = bpm;
	mBeatTime = 60.0 / mBPM;
}

void BPMPlayer::Start()
{
	mIsUpdate = true;
}

void BPMPlayer::Stop()
{
	mIsUpdate = false;
	mCurrentTime = 0;
}
