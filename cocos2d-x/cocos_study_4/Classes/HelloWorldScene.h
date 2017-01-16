#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	ParallaxNode *tpNode = nullptr;
	Sprite * tSprDragon = nullptr;
	bool mIsLeft = false;
	bool mIsRight = false;
	bool mIsUp = false;
	bool mIsDown = false;

	ActionCamera * mpCamera = nullptr;

	Sprite * mpSpr_0 = nullptr;
	Sprite * mpSpr_1 = nullptr;
	int mState = 0;

	void DoBackFlip();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event * event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event * event) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void update(float dt) override;

	virtual bool onTouchBegan(Touch * tTouch, Event * tEvnet) override;
	virtual void onTouchMoved(Touch * tTouch, Event * tEvnet) override;

};

#endif // __HELLOWORLD_SCENE_H__
