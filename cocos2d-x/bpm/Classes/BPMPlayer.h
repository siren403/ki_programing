#ifndef __BPMPLAYER_H__
#define __BPMPLAYER_H__

#include "cocos2d.h"
#include <functional>

USING_NS_CC;

typedef std::function<void(int)> CallBackBPM;


class BPMPlayer : public Node
{
private:
	double mCurrentTime = 0;
	int mBPM = 100;
	double mBeatTime = 0.0;
	bool mIsUpdate = false;

	int mTempo = 8;
	int mCurrentTempo = 0;

	CallBackBPM mCallBackBPM = nullptr;
public:
	virtual void update(float dt) override;
	virtual bool init() override;

	void SetCallBackBPM(CallBackBPM callBack);
	void SetBPM(int bpm);
	void Start();
	void Stop();

	CREATE_FUNC(BPMPlayer);
};

#endif // !__BPMPLAYER_H__
