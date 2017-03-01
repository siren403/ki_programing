#ifndef __TIMER_H__
#define __TIMER_H__

#include "cocos2d.h"

using namespace cocos2d;

class StopWatch : public Node
{
private:
	enum State
	{
		None = 0,
		Play = 1,
		Stop = 2,
		Pause = 3,
	};
	float mCurrentTime;
	StopWatch::State mState;
public:
	CREATE_FUNC(StopWatch);

	virtual bool init() override;
	virtual void update(float dt) override;

	void SetAutoUpdate(bool isUpdate);

	//GetAccTime
	float GetAccTime();

	void OnStart(float initTime = 0);
	void OnUpdate(float dt);
	float OnStop();
	float OnPause();
	void OnReset();

};

#endif // !__TIMER_H__
