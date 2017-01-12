#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void HelloWorld::Do()
{
}

void HelloWorld::DoWithBatch()
{
}

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


/*
	auto tKeyListener = EventListenerKeyboard::create();
	tKeyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	tKeyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyListener, this);
*/


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
 //   
 //   auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
 //   
 //   // position the label on the center of the screen
 //   label->setPosition(Vec2(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - label->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(label, 1);

 //   // add "HelloWorld" splash screen"
 //   mpSprActor = Sprite::create("HelloWorld.png");
	//mpSprActor->retain();

 //   // position the sprite on the center of the screen
	//mpSprActor->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(mpSprActor, 0);
    

	auto tSpriteA = Sprite::create("grossini_dance_01.png");
	log("spriteA refCount : %d", tSpriteA->getReferenceCount());
	

	tSpriteA->setPosition(visibleSize.width * 0.3f, visibleSize.height * 0.5f);
	this->addChild(tSpriteA, 1);

	auto tAnimation = Animation::create();
	tAnimation->setDelayPerUnit(0.3f);
	tAnimation->addSpriteFrameWithFile("grossini_dance_01.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_02.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_03.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_04.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_05.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_06.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_07.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_08.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_09.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_10.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_11.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_12.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_13.png");
	tAnimation->addSpriteFrameWithFile("grossini_dance_14.png");

	auto tAnimate = Animate::create(tAnimation);
	auto tRepeatForever = RepeatForever::create(tAnimate);
	tSpriteA->runAction(tRepeatForever);

	float tWidth = 0.0f;
	float tHeight = 0.0f;

	auto tSpriteSrc = Sprite::create("grossini_dance_atlas.png");
	auto tTexture = tSpriteSrc->getTexture();

	tWidth = 85;
	tHeight = 121;

	int tRow = 0;
	int tCol = 0;
	auto tAnimationB = Animation::create();
	tAnimationB->setDelayPerUnit(0.3f);

	for (int ti = 0; ti < 14; ti++)
	{
		tRow = ti / 5;
		tCol = ti % 5;

		tAnimationB->addSpriteFrameWithTexture(tTexture, Rect(tCol*tWidth, tRow*tHeight, tWidth, tHeight));
	}

	auto tSpriteB = Sprite::create("grossini_dance_atlas.png", Rect(0, 0, tWidth, tHeight));
	tSpriteB->setPosition(visibleSize.width * 0.7f, visibleSize.height*0.5f);
	this->addChild(tSpriteB, 2);

	auto tAnimateB = Animate::create(tAnimationB);
	auto tRepeatForeverB = RepeatForever::create(tAnimateB);
	tSpriteB->runAction(tRepeatForeverB);

	/*auto tCache = SpriteFrameCache::getInstance();
	tCache->addSpriteFramesWithFile("grossini_dance.plist");

	Vector<SpriteFrame *> tSpriteFrameVec;
	SpriteFrame * tSpriteFrame = NULL;

	char tStr[512];
	memset(tStr, 0, 512);

	for (int ti = 1; ti < 15; ti ++ )
	{
		tSpriteFrame = NULL;

		sprintf(tStr, "grossini_dance_%02d.png", ti);
		log(tStr);

		tSpriteFrame = tCache->getSpriteFrameByName(tStr);
		tSpriteFrameVec.pushBack(tSpriteFrame);
	}

	auto tAnimationC = Animation::createWithSpriteFrames(tSpriteFrameVec, 0.3f);
	auto tAnimateC = Animate::create(tAnimationC);
	auto tRepeatForeverC = RepeatForever::create(tAnimateC);
	*/


	//auto tSpriteC = Sprite::create();//현재
	//tSpriteC->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
	//this->addChild(tSpriteC, 3);

	//CSimpleAnimate::addPlist("grossini_dance.plist");

	//tSpriteC->runAction(CSimpleAnimate::CreateAction("grossini_dance_%02d.png", 1, 14));

	//create시 ref:1 autoReleasePool에 등록
	mSpriteC = Sprite::create();
	log("ref count : %d", mSpriteC->getReferenceCount());

	mSpriteC->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
	//ref++ -> ref:2, 부모 해제 시 ref-- -> ref:1
	//
	this->addChild(mSpriteC, 3);
	log("ref count : %d", mSpriteC->getReferenceCount());

	CSimpleAnimate::addPlist("grossini_dance.plist");

	mSpriteC->runAction(CSimpleAnimate::CreateAction("grossini_dance_%02d.png", 1, 14));
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if (NULL != mpSprActor)
	{
		mpSprActor->release();
		mpSprActor = NULL;
	}

	_eventDispatcher->removeAllEventListeners();

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	/*mpListenerMouse = EventListenerMouse::create();

	mpListenerMouse->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	mpListenerMouse->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	mpListenerMouse->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	mpListenerMouse->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListenerMouse,this);*/

	/*mpListener = EventListenerTouchOneByOne::create();
	mpListener->setSwallowTouches(true);
	mpListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	mpListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	mpListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);*/

	//mpListenerCustom = EventListenerCustom::create(
	//	"custom_event",
	//	CC_CALLBACK_1(HelloWorld::OnCustomEvent, this)
	//);

	//_eventDispatcher->addEventListenerWithFixedPriority(mpListenerCustom, 1);

	//char tBuffer[512];
	//memset(tBuffer, 0, 512);
	//sprintf(tBuffer, "%s", "Event Test");

	////param
	////1. string : eventName
	//EventCustom tEventCustom("custom_event");
	//tEventCustom.setUserData(tBuffer);
	//_eventDispatcher->dispatchEvent(&tEventCustom);

}

void HelloWorld::onExit()
{
	//_eventDispatcher->removeEventListener(mpListenerMouse);
	//_eventDispatcher->removeEventListener(mpListener);
	//_eventDispatcher->removeEventListener(mpListenerCustom);
	Layer::onExit();
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	auto isRight = mouseEvent->getMouseButton();

	if (isRight == 0)
	{
		mpSprActor->setPosition(ClickPoint);
	}
	
	log("onMouseDown : %d",isRight);
}
void HelloWorld::onMouseUp(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	auto isRight = mouseEvent->getMouseButton();
	if (isRight == 0)
	{
		mpSprActor->setPosition(ClickPoint);
	}
	log("onMouseUp");
}
void HelloWorld::onMouseMove(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	//mpSprActor->setPosition(ClickPoint);

	log("onMouseMove : (%d,%d)", ClickPoint.x, ClickPoint.y);
}
void HelloWorld::onMouseScroll(cocos2d::Event * event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	log("onMouseScroll");
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	bool tIsTouch = mpSprActor->getBoundingBox().containsPoint(tTouchPos);

	if (tIsTouch)
	{
		log("sprite is touched");
	}

	return true;
}
void HelloWorld::onTouchMoved(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	log("x:%f, y:%f, id:%d", tTouchPos.x, tTouchPos.y, touch->getID());

	bool tIsTouch = mpSprActor->getBoundingBox().containsPoint(tTouchPos);

	if (tIsTouch)
	{
		mpSprActor->setPosition(tTouchPos);
	}

	//이벤트 메소드를 호출하는 리스너를 가진 대상 노드
	//ex) this->pos == (50,0)
	//	  taget->pos = (50,0)
	Vec2 tVec = unused_event->getCurrentTarget()->getPosition();
	log("[target] x:%f, y:%f", tVec.x, tVec.y);
}
void HelloWorld::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	log("x:%f, y:%f, id:%d", tTouchPos.x, tTouchPos.y, touch->getID());

	bool tIsTouch = mpSprActor->getBoundingBox().containsPoint(tTouchPos);

}
void HelloWorld::onTouchCancelled(Touch * touch, Event * unused_event)
{

}

void HelloWorld::OnCustomEvent(EventCustom * tEvent)
{
	char *tpBuffer = (char *)(tEvent->getUserData());

	std::string tString = "OnCustomEvent ";
	tString = tString + tpBuffer;


	log("OnCustomEvent: %s", tString.c_str());
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	Vec2 tVec = mpSprActor->getPosition();
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		tVec.x -= 10;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		tVec.x += 10;
		break;
	}
	mpSprActor->setPosition(tVec);
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
{
}
