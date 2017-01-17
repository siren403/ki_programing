#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CGrid;

class HelloWorld : public cocos2d::Layer
{
protected:
	EventListenerTouchOneByOne * mpListener = nullptr;

	Label * mplblTest = nullptr;
public:
	CGrid * mpGrid = nullptr;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;
	virtual void onTouchCancelled(Touch * touch, Event * unused_event) override;


};

#endif // __HELLOWORLD_SCENE_H__
