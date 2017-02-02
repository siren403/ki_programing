#ifndef __SCENERENDERTEXTURE_H__
#define __SCENERENDERTEXTURE_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneRenderTexture : public LayerColor
{
private:
	RenderTexture * mpRenderTexture = nullptr;
	Sprite * mpRenderSprite = nullptr;
	GLProgram * mpGLProgram = nullptr;
	GLProgramState * mpGLState = nullptr;
	Node * mpRenderNode = nullptr;

	Vec2 mMousePos;
	float mCurrentLensSize = 0;
	float mCurrentLensOutLine = 0;
	float mCurrentLensInLine = 0;

	float mCurrentTime = 0;
public:
	static Scene * createScene();
	CREATE_FUNC(SceneRenderTexture);

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;

	virtual bool onTouchBegan(Touch * tTouch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * tTouch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * tTouch, Event * unused_event) override;

};

#endif // !__SCENERENDERTEXTURE_H__
