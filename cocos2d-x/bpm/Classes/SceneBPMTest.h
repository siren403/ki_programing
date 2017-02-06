#ifndef __SCENEBPMTEST_H__
#define __SCENEBPMTEST_H__

#include "cocos2d.h"

USING_NS_CC;

class BPMPlayer;

class SceneBPMTest : public LayerColor
{
private:
	BPMPlayer * mBPMPlayer = nullptr;
	char * mSEName = "sounds/flockstep/step.wav";
	char * mBGMName = "sounds/flockstep/step_short_final.wav";
	bool mIsPlaying = false;
public:
	static Scene * createScene();
	virtual bool init() override;

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event * event);

	void ReceiveBPM(int tempo);
	CREATE_FUNC(SceneBPMTest);
};

#endif // !__SCENEBPMTEST_H__
