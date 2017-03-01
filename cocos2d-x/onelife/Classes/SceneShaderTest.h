#ifndef __SCENESHADERTEST_H__
#define __SCENESHADERTEST_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneShaderTest : public LayerColor
{
	
public:
	static Scene * createScene();
	CREATE_FUNC(SceneShaderTest);
	virtual bool init() override;
	virtual void update(float dt) override;
private:
	GLProgramState * mGLState = nullptr;
	float mCurrentTime = 0;
};

#endif // !__SCENESHADERTEST_H__
