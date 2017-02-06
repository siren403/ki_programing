#ifndef __SHADERTEST_H__
#define __SHADERTEST_H__

#include "cocos2d.h"

using namespace cocos2d;

class ShaderTest : public Node
{
private:
	Sprite * mSprite = nullptr;
	Sprite * mAimSprite = nullptr;
	Vec2 mMousePos;
	GLProgramState * mGLState = nullptr;
	float mCurrentLensSize = 0;
	float mCurrentLensOutLine = 0;
	float mCurrentLensInLine = 0;

public:
	CREATE_FUNC(ShaderTest);
	virtual bool init() override;
	virtual void update(float dt);

	virtual void onExit() override;
	Vec2 GetUV(Vec2 tTexCoord,Vec2 tResolution,Vec2 tMousePos);

	bool OnTouchBegan(Touch * tTouch, Event * unused_event);
	void OnTouchMoved(Touch * tTouch, Event * unused_event);
	void OnTouchEnded(Touch * tTouch, Event * unused_event);

};
#endif // !__SHADERTEST_H__
