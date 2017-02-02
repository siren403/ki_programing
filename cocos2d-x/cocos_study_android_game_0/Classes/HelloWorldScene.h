#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
private:
	RenderTexture * mpRenderTexture = nullptr;
	Sprite * mpRenderSprite = nullptr;
	GLProgram * mpGLProgram = nullptr;
	GLProgramState * mpGLState = nullptr;
	Node * mpRenderNode = nullptr;
	Node * mpSpritesNode = nullptr;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;
};

#endif // __HELLOWORLD_SCENE_H__
