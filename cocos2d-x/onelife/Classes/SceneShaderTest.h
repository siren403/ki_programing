#ifndef __SCENESHADERTEST_H__
#define __SCENESHADERTEST_H__

#include "cocos2d.h"

using namespace cocos2d;

class ShaderWrapper;
class SWDrawCircle;
class SWDrawArc;

class SceneShaderTest : public LayerColor
{
	
public:
	static Scene * createScene();
	CREATE_FUNC(SceneShaderTest);
	virtual bool init() override;
	virtual void update(float dt) override;

	virtual void onExit() override;
private:
	GLProgramState * mGLState = nullptr;
	float mCurrentTime = 0;

	ShaderWrapper * mDrawShader = nullptr;

	SWDrawCircle * mPlayerHitCircle = nullptr;
	SWDrawArc * mDrawArc = nullptr;
};

#endif // !__SCENESHADERTEST_H__
