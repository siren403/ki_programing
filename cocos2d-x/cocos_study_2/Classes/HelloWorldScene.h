#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CSimpleAnimate.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
protected:
	Sprite * mpSprActor = NULL;
	Vec2 mVecActor;

	EventListenerMouse * mpListenerMouse = NULL;
	EventListenerTouchOneByOne * mpListener = NULL;

	//커스텀 이벤트 리스너
	EventListenerCustom * mpListenerCustom = NULL;

	void Do();
	void DoWithBatch();

	Sprite * mSpriteC = NULL;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onEnter() override;
	virtual void onExit() override;

	//mouse
	virtual void onMouseDown(cocos2d::Event* event);
	virtual void onMouseUp(cocos2d::Event* event);
	virtual void onMouseMove(cocos2d::Event* event);
	virtual void onMouseScroll(cocos2d::Event* event);

	//touch
	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;
	//전화가 올 경우 사용?
	virtual void onTouchCancelled(Touch * touch, Event * unused_event) override;

	//커스텀
	void OnCustomEvent(EventCustom * tEvent);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event * event) override;
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event * event) override;

	
};

#endif // __HELLOWORLD_SCENE_H__
