#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "cocos2d.h"
#include <functional>
#include <vector>

using namespace cocos2d;
using namespace std;

class StopWatch;

typedef function<bool(float)> UpdateFunc;

class SceneTitle : public LayerColor
{
public:
	static Scene * createScene();
	CREATE_FUNC(SceneTitle);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

	virtual void onAcceleration(Acceleration * acc, Event * unused_event) override;
private:
	Size mVisibleSize;
	Vec2 mCenterPosition;
	Sprite * mMask = nullptr;
	Vec2 mMaskInitPosition;

	Node * mRenderNode = nullptr;
	RenderTexture * mRenderTexture = nullptr;
	Sprite * mRenderSprite = nullptr;
	GLProgramState * mGLState = nullptr;

	Vec2 mLensPosition;
	Vec2 mLensTargetPosition;

	StopWatch * mStopWatch = nullptr;

	//sequence update
	int mUpdateFunctionIndex = 0;
	vector<UpdateFunc> mUpdateFunctions;
	StopWatch * mUpdateFunctionWatch = nullptr;

	Sprite * mExclamationMark = nullptr;
	int mTitleScriptIndex = 0;
	int mScriptCharIndex = 0;
	vector<string> mTitleScript;
	Label * mTitleScriptLabel = nullptr;

	//touch State
	bool mIsTouchBegan = false;

	void SetLensTargetPosition(Vec2 pos);
};

#endif // !__SCENETITLE_H__
