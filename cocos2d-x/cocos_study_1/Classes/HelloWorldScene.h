#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	Sprite * mpSprBall = NULL;
	Action * mpAction = NULL;
	enum {
		STATE_MOVE = 0,
		STATE_ROTATE = 1,
		STATE_SCALE = 2,
		STATE_JUMP = 3,
		STATE_TINT = 4,
		STATE_BEZIER = 5,
		STATE_PLACE = 6,
		STATE_BLINK = 7,
		STATE_FADEOUT = 8,
		STATE_FADEIN = 9
	};



	enum {
		TYPE_TO = 0,
		TYPE_BY = 1
	};


	unsigned int mState = 0;
	unsigned int mType = 0;

	enum
	{
		TYPE_EASE = 0,
		TYPE_ELASTIC = 1,
		TYPE_BOUNCE = 2,
		TYPE_SPEED = 3
	};


	Action *mpMove = NULL;
	Action *mpEaseIn = NULL;
	Action *mpEaseOut = NULL;
	Action *mpEaseInOut_1 = NULL;
	Sprite *mpBall_0 = NULL;
	Sprite *mpBall_1 = NULL;
	Sprite *mpBall_2 = NULL;
	Sprite *mpBall_3 = NULL;

	void DoActionReset();
	void DoActionWithStateAndType();
	void DoAction(Ref * PSender);

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void CallBack1();
	void CallBack2(Node * sender);
	void CallBack3(Node * sender,long data);


};

#endif // __HELLOWORLD_SCENE_H__
