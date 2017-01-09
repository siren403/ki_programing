#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Sprite * mpSpriteHelloWorld = NULL;
	cocos2d::Label * mpLabel = NULL;

	Sprite * mpSprBall = NULL;
	Vec2 mVecBall;
	Label * mpLabel_0 = NULL;
	Label * mpLabel_1 = NULL;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	void OnClickBtnTest(Ref * pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
