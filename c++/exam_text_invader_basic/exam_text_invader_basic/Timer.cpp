#include "stdafx.h"
#include "Timer.h"
#include <Windows.h>

CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

void CTimer::SetInterval(int tInterval)
{
	mInterval = tInterval;
}

void CTimer::Init()
{
	if (mStartTime == 0)
	{
		mStartTime = GetTickCount();
	}
}

void CTimer::Update()
{
	mCurrentTime = GetTickCount();
}

bool CTimer::Check()
{
	if (mCurrentTime - mStartTime >= mInterval)
	{
		mStartTime = mCurrentTime;
		return true;
	}
	return false;
}
