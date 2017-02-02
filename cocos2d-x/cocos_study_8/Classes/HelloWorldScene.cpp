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

    
	mpLabel = Label::create("Hello World", "fonts/Marker Felt.ttf", 24);

	mpLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - mpLabel->getContentSize().height));
	this->addChild(mpLabel, 1);

	mpSpriteB = Sprite::create("CloseNormal.png");
	mVecB.x = 350.0f;
	mVecB.x = 350.0f;
	mpSpriteB->setPosition(mVecB);

	this->addChild(mpSpriteB);

	mpSpriteA = Sprite::create("idle_00.png");
	mpSpriteA->setPosition(Vec2(240.0f, 160.0f));
	this->addChild(mpSpriteA);


	Size tSizeA = mpSpriteA->getContentSize();
	int tRow = 0;
	int tCol = 0;
	int tIndex = 0;

	
	mpImageA = new Image();
	mpImageA->initWithImageFile("idle_00.png");

	int tLen = tSizeA.width * tSizeA.height * 4;

	log("mpImage : %d", tLen);
	log("mpImage.data Len: %d", mpImageA->getDataLen());

	auto tKeyListener = EventListenerKeyboard::create();
	tKeyListener->onKeyPressed = [this](EventKeyboard::KeyCode tKeyCode,Event * tEvent) 
	{
		switch (tKeyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			mVecB.x -= 2.0f;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			mVecB.x += 2.0f;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			mVecB.y += 2.0f;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			mVecB.y -= 2.0f;
			break;
		}
		
		mpSpriteB->setPosition(mVecB);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyListener, this);

	this->scheduleUpdate();



	//================ render Texture

	Size tWinSize = Director::getInstance()->getWinSize();
	RenderTexture * tpTexture = nullptr;
	tpTexture = RenderTexture::create(tWinSize.width, tWinSize.height,
		Texture2D::PixelFormat::RGBA8888);
	this->addChild(tpTexture, 100);

	tpTexture->begin();
	//tpTexture->beginWithClear(1.0, 1.0, 1.0, 1.0);
	this->visit();
	tpTexture->end();

	tpTexture->setPosition(Vec2(300, 250));
	tpTexture->setScale(0.4f);

    return true;
}

void HelloWorld::update(float dt)
{
	if (true == IsCollision())
	{
		if (nullptr != mpLabel)
		{
			mpLabel->setString("collision");
		}
	}
	else
	{
		if (nullptr != mpLabel)
		{
			mpLabel->setString("not collision");
		}
	}
}


bool HelloWorld::IsCollision()
{
	bool tResult = false;

	Rect tRectA = mpSpriteA->getBoundingBox();
	Rect tRectB = mpSpriteB->getBoundingBox();

	if (true == tRectA.intersectsRect(tRectB))
	{
		Vec2 tVecIn = mpSpriteA->convertToNodeSpace(mVecB);

		int tX = tVecIn.x;
		int tY = tVecIn.y;

		if (tX<0 || tX>mpSpriteA->getContentSize().width ||
			tY<0 || tY>mpSpriteA->getContentSize().height)
		{
			return false;
		}

		tY = mpSpriteA->getContentSize().height - tY;

		unsigned char * pData = mpImageA->getData();


		int tIndex = (tY*mpSpriteA->getContentSize().width + tX) * 4 + 3;
		unsigned char tAlpha = pData[tIndex];


		if (0 != tAlpha)
		{
			tResult = true;
		}
		else
		{
			tResult = false;
		}
	}

	return tResult;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
