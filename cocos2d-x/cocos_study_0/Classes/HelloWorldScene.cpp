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

	auto tBtnTest = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::OnClickBtnTest, this));

	tBtnTest->setPosition(Vec2(20,20));

    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, tBtnTest, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

	//(1)
 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//mpLabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//mpLabel->retain();

 //   
 //   // position the label on the center of the screen
	//mpLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - mpLabel->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(mpLabel, 1);

 //   // add "HelloWorld" splash screen"
 //   //auto sprite = Sprite::create("HelloWorld.png");
	//mpSpriteHelloWorld = Sprite::create("HelloWorld.png");
	//mpSpriteHelloWorld->retain();

 //   // position the sprite on the center of the screen
	//mpSpriteHelloWorld->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//mpSpriteHelloWorld->runAction(MoveBy::create(2, Vec2(50, 10)));

 //   // add the sprite as a child to this layer
 //   this->addChild(mpSpriteHelloWorld, 0);
    
	//(2)
	/*mpSprBall = Sprite::create("images/grossinis_sister1.png");
	mpSprBall->retain();
	mpSprBall->setAnchorPoint(Vec2(0.5, 0.0));

	mVecBall.x = 240;
	mVecBall.y = 0;
	mpSprBall->setPosition(mVecBall);
	this->addChild(mpSprBall, 2);

	auto tSprite = Sprite::create("images/grossini.png");
	tSprite->setPosition(Vec2(0,0));
	tSprite->setAnchorPoint(Vec2(0.2, 0.0));
	mpSprBall->addChild(tSprite, 1);

	mpSprBall->setVisible(false);


	mpLabel_0 = Label::createWithBMFont("fonts/boundsTestFont.fnt", "I am a good boy.");
	mpLabel_0->retain();

	Vec2 tVecLabel;
	tVecLabel.x = 240;
	tVecLabel.y = 160;
	mpLabel_0->setPosition(tVecLabel);

	this->addChild(mpLabel_0, 1);


	mpLabel_1 = Label::createWithCharMap("fonts/larabie-16.plist");
	mpLabel_1->retain();

	tVecLabel.x = 240;
	tVecLabel.y = 160 - 40;
	mpLabel_1->setPosition(tVecLabel);

	mpLabel_1->setString("GOODBOYzzzz...");

	this->addChild(mpLabel_1, 2);*/

	mpSprBall = Sprite::create("Images/grossini.png");
	//parent->setTextureRect(Rect(0, 0, 150, 150));
	mpSprBall->setPosition(Vec2(240, 160));
	//parent->setColor(Color3B(0, 0, 255));
	this->addChild(mpSprBall);

	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 5));
	child->setColor(Color3B::RED);

	Size parentSize;
	parentSize = mpSprBall->getContentSize();
	child->setPosition(Vec2(parentSize.width / 2.0, parentSize.height + 10));
	mpSprBall->addChild(child);

	mpSprBall->runAction(EaseBackInOut::create(MoveBy::create(3, Vec2(100, 0))));

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

	this->removeChild(mpLabel_1);
	if (NULL != mpLabel_1)
	{
		mpLabel_1->release();
		mpLabel_1 = NULL;
	}

	this->removeChild(mpLabel_0);
	if (NULL != mpLabel_0)
	{
		mpLabel_0->release();
		mpLabel_0 = NULL;
	}

	this->removeChild(mpSprBall);
	if (NULL != mpSprBall)
	{
		mpSprBall->release();
		mpSprBall = NULL;
	}

	/*this->removeChild(mpSpriteHelloWorld);
	this->removeChild(mpLabel);

	if (mpSpriteHelloWorld != NULL)
	{
		mpSpriteHelloWorld->release();
		mpSpriteHelloWorld = NULL;
	}
	if (mpLabel != NULL)
	{
		mpLabel->release();
		mpLabel = NULL;
	}*/

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::OnClickBtnTest(Ref * pSender)
{
	mpSprBall->setVisible(!mpSprBall->isVisible());
}
