#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
private:
	Sprite * mpSprHello = NULL;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float dt) override;

	void myTick(float f);
	void callEveryFrame(float f);
	void myTickOnce(float f);
	int nNum;

	ProgressTimer * pt = NULL;
	void SpriteProgressToRadial(float f);


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	void doPushScene(Ref* pSender);
	void doPushSceneTran(Ref* pSender);
	void doReplaceScene(Ref* pSender);
	void doReplaceSceneTran(Ref* pSender);
	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

};

#endif // __HELLOWORLD_SCENE_H__
