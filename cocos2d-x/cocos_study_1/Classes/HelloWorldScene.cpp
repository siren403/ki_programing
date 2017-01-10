#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));


	MenuItemFont::setFontSize(14);

	auto pMenuItem = MenuItemFont::create(
		"DoAction",
		CC_CALLBACK_1(HelloWorld::DoAction, this)
	);
	pMenuItem->setColor(Color3B(255, 255, 0));
	pMenuItem->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, pMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	
	//mpSprBall = Sprite::create("grossini.png");
	//mpSprBall->retain();
	//mpSprBall->setPosition(Vec2(50, 200));
	//this->addChild(mpSprBall, 1);


	mpBall_0 = Sprite::create("CloseNormal.png");
	mpBall_0->setPosition(Vec2(50, 250));
	mpBall_0->setScale(0.7f);
	this->addChild(mpBall_0);

	mpBall_1 = Sprite::create("CloseNormal.png");
	mpBall_1->setPosition(Vec2(50, 200));
	mpBall_1->setScale(0.7f);
	this->addChild(mpBall_1);

	mpBall_2 = Sprite::create("CloseNormal.png");
	mpBall_2->setPosition(Vec2(50, 150));
	mpBall_2->setScale(0.7f);
	this->addChild(mpBall_2);

	mpBall_3 = Sprite::create("CloseNormal.png");
	mpBall_3->setPosition(Vec2(50, 100));
	mpBall_3->setScale(0.7f);
	this->addChild(mpBall_3);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if (mpBall_0 != nullptr)
	{
		mpBall_0->release();
		mpBall_0 = nullptr;
	}
	if (mpBall_1 != nullptr)
	{
		mpBall_1->release();
		mpBall_1 = nullptr;
	}
	if (mpBall_2 != nullptr)
	{
		mpBall_2->release();
		mpBall_2 = nullptr;
	}
	if (mpBall_3 != nullptr)
	{
		mpBall_3->release();
		mpBall_3 = nullptr;
	}

	this->removeChild(mpSprBall);
	if (NULL != mpSprBall)
	{
		mpSprBall->release();
		mpSprBall = NULL;
	}

	if (NULL != mpAction)
	{
		mpAction->release();
		mpAction = NULL;
	}


    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::CallBack1()
{
	/*auto action_0 = TintTo::create(1, Color3B(160, 75, 200));
	mpSprBall->runAction(action_0);*/
	mpSprBall->setColor(Color3B(255, 255, 255));
}

void HelloWorld::CallBack2(Node * sender)
{
	/*auto action_1 = ScaleTo::create(2, 7, 4);
	((Sprite *)sender)->runAction(action_1);*/
	((Sprite *)sender)->setScale(1);
}

void HelloWorld::CallBack3(Node * sender, long data)
{
	/*
	auto action_2 = Blink::create(3, data);
	mpSprBall->runAction(action_2);*/
	((Sprite *)sender)->setPosition(Vec2(240,180));

}


void HelloWorld::DoAction(Ref * PSender)
{
	//mpAction = MoveBy::create(2, Vec2(mpSprBall->getPosition().x == 0 ? 400 : 0, 0));
	
	//mpAction = JumpTo::create(2, Vec2(400, 200), 50, 3);

	/*ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Vec2(150, 150);
	bezier1.controlPoint_2 = Vec2(250, -150);
	bezier1.endPosition = Vec2(350, 0);

	mpAction = BezierTo::create(3, bezier1);
	mpSprBall->runAction(mpAction);*/

	//mState = 1;
	//mType = 0;


	//DoActionWithStateAndType();

	
	/*auto action_0 = TintTo::create(1, Color3B(255, 0, 0));
	auto action_1 = TintTo::create(1, Color3B(0, 0, 255));
	auto action_2 = TintTo::create(1, Color3B(0, 255, 0));

	auto Seq = Sequence::create(
		action_0,
		action_1,
		action_2,
		NULL
	);
	auto repeat_0 = Repeat::create(Seq, 3);
	auto repeat_1 = RepeatForever::create(Seq);
	mpSprBall->runAction(repeat_1);
*/

	//auto action_0 = TintTo::create(1, Color3B(160, 75, 200));
	//auto action_1 = ScaleTo::create(2, 7, 4);
	//auto action_2 = Blink::create(3, 20);


	//auto spawn = Spawn::create(
	//	Sequence::create(
	//		action_0,
	//		CallFunc::create(CC_CALLBACK_0(HelloWorld::CallBack1, this)),
	//		NULL
	//		),
	//	Sequence::create(
	//		action_1,
	//		CallFunc::create(CC_CALLBACK_0(HelloWorld::CallBack2, this, mpSprBall)),
	//		NULL
	//	),
	//	Sequence::create(
	//		action_2,
	//		CallFunc::create(CC_CALLBACK_0(HelloWorld::CallBack3, this, mpSprBall, 50)),
	//		NULL
	//	),
	//	NULL
	//);


	//mpSprBall->runAction(spawn);

	mType = 1;

	DoActionReset();

	mpMove = MoveBy::create(3.0f, Vec2(400, 0));

	switch (mType)
	{
	case TYPE_EASE:

		mpEaseIn = EaseIn::create(static_cast<ActionInterval *>(mpMove->clone()), 3.0f);
		mpEaseOut = EaseOut::create(static_cast<ActionInterval *>(mpMove->clone()), 3.0f);
		mpEaseInOut_1 = EaseInOut::create(static_cast<ActionInterval *>(mpMove->clone()), 3.0f);
		break;
	case TYPE_ELASTIC:
	{
		mpEaseIn = EaseElasticIn::create(static_cast<ActionInterval *>(mpMove->clone()), 0.4f);
		mpEaseOut = EaseElasticOut::create(static_cast<ActionInterval *>(mpMove->clone()), 0.4f);
		mpEaseInOut_1 = EaseElasticInOut::create(static_cast<ActionInterval *>(mpMove->clone()), 0.4f);
	}
	break;
	case TYPE_BOUNCE:
	{

		mpEaseIn = EaseBounceIn::create(static_cast<ActionInterval *>(mpMove->clone()));
		mpEaseOut = EaseBounceOut::create(static_cast<ActionInterval *>(mpMove->clone()));
		mpEaseInOut_1 = EaseBounceInOut::create(static_cast<ActionInterval *>(mpMove->clone()));
	}
	break;
	case TYPE_SPEED:
	{

		mpEaseIn = Speed::create(static_cast<ActionInterval *>(mpMove->clone()), 2.0);
		mpEaseOut = Speed::create(static_cast<ActionInterval *>(mpMove->clone()), 3.0);
		mpEaseInOut_1 = Speed::create(static_cast<ActionInterval *>(mpMove->clone()), 4.0);

	}
	break;
	}

	mpBall_0->runAction(mpMove);
	mpBall_1->runAction(mpEaseIn);
	mpBall_2->runAction(mpEaseOut);
	mpBall_3->runAction(mpEaseInOut_1);
}

void HelloWorld::DoActionReset()
{
	mpBall_0->setPosition(Vec2(50, 250));
	mpBall_0->setScale(0.7f);

	mpBall_1->setPosition(Vec2(50, 200));
	mpBall_1->setScale(0.5f);

	mpBall_2->setPosition(Vec2(50, 150));
	mpBall_2->setScale(0.5f);

	mpBall_3->setPosition(Vec2(50, 100));
	mpBall_3->setScale(0.5);
}

void HelloWorld::DoActionWithStateAndType()
{
	// by는 현재 값에서 지정한 값만큼 변하는 액션 수행
	// to는 지정한 값으로 변하는 액션 수행

	// RotateTo : 결과에 가까운 쪽으로 최소한으로 회전한다. 180, 270, 540
	// RotateBy : 적힌 숫자만큼 시계방향으로 회전한다. 180, 270, 540
	// ScaleTo  : 원래 크기 대비 1회 증가
	// ScaleBy  : 계속 증가

	switch (mState)
	{
	case STATE_MOVE:
	{
		if (TYPE_TO == mType)
		{
			mpAction = MoveTo::create(2, Vec2(400, 0));

		}
		else if (TYPE_BY == mType)
		{
			mpAction = MoveBy::create(2, Vec2(400, 0));
		}
	}
	break;
	case STATE_ROTATE:
	{
		if (TYPE_TO == mType)
		{
			mpAction = RotateTo::create(2, 270);
		}
		else if (TYPE_BY == mType)
		{
			mpAction = RotateBy::create(2, 270);
		}
	}
	break;
	case STATE_SCALE:
	{
		if (TYPE_TO == mType)
		{
			mpAction = ScaleTo::create(2, 2.0);
		}
		else if (TYPE_BY == mType)
		{
			mpAction = ScaleBy::create(2, 2.0);
		}
	}
	break;
	case STATE_JUMP:
	{
		if (TYPE_TO == mType)
		{
			mpAction = JumpTo::create(2, Vec2(400, 0), 50, 3);
		}
		else if (TYPE_BY == mType)
		{
			mpAction = JumpBy::create(2, Vec2(400, 0), 50, 3);
			//mpAction = JumpBy::create(0.5, Vec2(0, 0), 70, 1);
		}
	}
	break;



	case STATE_TINT:
	{
		if (TYPE_TO == mType)
		{
			mpAction = TintTo::create(2, 128, 128, 128);
		}
		else if (TYPE_BY == mType)
		{
			mpAction = TintBy::create(2, 0, -30, 30);
		}
	}
	break;

	case STATE_BEZIER:
	{
		ccBezierConfig bezier1;
		bezier1.controlPoint_1 = Vec2(150, 150);
		bezier1.controlPoint_2 = Vec2(250, -150);
		bezier1.endPosition = Vec2(350, 0);

		ccBezierConfig bezier2;
		bezier2.controlPoint_1 = Vec2(200, 150);
		bezier2.controlPoint_2 = Vec2(200, 150);
		bezier2.endPosition = Vec2(350, 0);

		if (TYPE_TO == mType)
		{
			mpAction = BezierTo::create(3, bezier1);
		}
		else if (TYPE_BY == mType)
		{
			mpAction = BezierBy::create(3, bezier1);
		}
	}
	break;


	case STATE_PLACE:
	{
		mpAction = Place::create(Vec2(300, 200));
	}
	break;
	case STATE_BLINK:
	{
		mpAction = Blink::create(2, 5);
	}
	break;
	case STATE_FADEOUT:
	{
		mpAction = FadeOut::create(1.5);
	}
	break;
	case STATE_FADEIN:
	{
		mpAction = FadeIn::create(1.5);
	}
	break;

	}

	mpSprBall->runAction(mpAction);
}
