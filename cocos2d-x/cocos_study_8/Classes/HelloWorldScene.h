#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
protected:
	Sprite * mpSpriteA = nullptr;
	Vec2 mVecA;
	Image * mpImageA = nullptr;

	Sprite * mpSpriteB = nullptr;
	Vec2 mVecB;

	Label * mpLabel = nullptr;

	bool IsCollision();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt) override;
};

#endif // __HELLOWORLD_SCENE_H__
