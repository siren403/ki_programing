#pragma once

//todo : issue
class CTimer
{
private:
	unsigned int mInterval = 1000;
	unsigned int mCurrentTime = 0;
	unsigned int mStartTime = 0;
public:
	CTimer();
	~CTimer();

	void SetInterval(float tInterval);
	void Init();
	void Update();
	bool Check();
};

