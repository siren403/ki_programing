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

	auto tLayer = Layer::create();
	this->addChild(tLayer, 0);

	tpNode = ParallaxNode::create();
#pragma region basic

	/*Sprite * tpSprCocos = Sprite::create("images/powered.png");
	tpSprCocos->setAnchorPoint(Vec2(0, 0));

	Sprite *tpSprBG = Sprite::create("images/background.png");
	tpSprBG->setAnchorPoint(Vec2(0, 0));

	tpNode->addChild(tpSprBG, 0, Vec2(1.0f, 0.0f), Vec2(0, -160));

	tpNode->addChild(tpSprCocos, 50, Vec2(2.0f, 1.0f), Vec2(240, 0));
*/
#pragma endregion

#pragma region img to img

	Sprite *tpBg_0 = Sprite::create("images/background1.png");
	tpBg_0->setAnchorPoint(Vec2(0, 0));
	
	Sprite *tpBg_1 = Sprite::create("images/background2.png");
	tpBg_1->setAnchorPoint(Vec2(0, 0));

	// 이미지가 만나는 가장자리(edge)에 검은선이 생기는 현상을 방지하기 위하여
	// Anti-Aliasing을 끈다.
	tpBg_0->getTexture()->setAliasTexParameters();
	tpBg_1->getTexture()->setAliasTexParameters();

	tpNode->addChild(tpBg_0, 0, Vec2(1,1), Vec2(0, 0));
	tpNode->addChild(tpBg_1, 0, Vec2(1,2), Vec2(512, 0));


#pragma region add dragon

	int tRow = 0;
	int tCol = 0;
	int ti = 0;


	auto texture = Director::getInstance()->getTextureCache()->addImage("images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (ti = 0; ti < 6; ti++) 
	{

		tCol = ti % 4;
		tRow = ti / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(tCol * 130, tRow * 140, 130, 140));

	}

	auto animate = Animate::create(animation);
	auto tRepeatForever = RepeatForever::create(animate);

	tSprDragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	tSprDragon->setPosition(Vec2(240, 160));
	tLayer->addChild(tSprDragon,1);

	tSprDragon->runAction(tRepeatForever);


#pragma endregion


#pragma endregion


#pragma region orbit camera

	mpSpr_0 = Sprite::create("images/f054.png");
	mpSpr_0->setScale(0.5f);
	mpSpr_0->setPosition(Vec2(240, 160));
	this->addChild(mpSpr_0, 10);

	mpSpr_1 = Sprite::create("images/f062.png");
	mpSpr_1->setScale(0.5f);
	mpSpr_1->setPosition(Vec2(240, 160));
	this->addChild(mpSpr_1, 10);

	mState = 0;

	mpSpr_0->setVisible(true);
	mpSpr_1->setVisible(false);

#pragma endregion



	/*auto go = MoveBy::create(4, Vec2(-160, -100.0f));
	auto goBack = go->reverse();
	auto tSequence = Sequence::create(go, goBack, nullptr);
	auto tRepeatForever = RepeatForever::create(tSequence);

	tpNode->runAction(tRepeatForever);*/

	tLayer->addChild(tpNode,0);
	tLayer->runAction(Follow::create(tSprDragon, Rect(0, 0, 512 * 2, 320)));


    return true;
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

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		mIsLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		mIsRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		mIsUp = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		mIsDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:


		if (0 == mState)
		{
			mState = 1;
		}
		else if (1 == mState)
		{
			mState = 0;
		}
		
		auto tFirstHalf = OrbitCamera::create(
			0.5f,
			1.0f, 0,
			0, 90.0f,
			0, 0);

		switch (mState)
		{
		case 0:
			mpSpr_0->runAction(tFirstHalf);
			break;
		case 1:
			mpSpr_1->runAction(tFirstHalf);
			break;
		}

		auto Seq = Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create(CC_CALLBACK_0(HelloWorld::DoBackFlip,this)),
			nullptr
		);

		this->runAction(Seq);

		break;
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		mIsLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		mIsRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		mIsUp = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		mIsDown = false;
		break;
	}
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	auto tKey = EventListenerKeyboard::create();
	tKey->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	tKey->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKey, this);
	this->scheduleUpdate();


#pragma region actionCamera

	auto tListener = EventListenerTouchOneByOne::create();
	tListener->setSwallowTouches(true);

	tListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	tListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tListener, this);

	mpCamera = new ActionCamera();
	mpCamera->startWithTarget(tSprDragon);

#pragma endregion

}

void HelloWorld::onExit()
{
	CC_SAFE_DELETE(mpCamera);

	this->unscheduleUpdate();
	_eventDispatcher->removeEventListenersForTarget(this);
	Layer::onExit();

}

void HelloWorld::update(float dt)
{
	Vec2 tVec = tSprDragon->getPosition();
	float speed = 3.5f;
	if (mIsLeft)
	{
		tVec.x -= speed;
	}
	else if (mIsRight)
	{
		tVec.x += speed;
	}

	if (mIsUp)
	{
		tVec.y += speed;
	}
	else if (mIsDown)
	{
		tVec.y -= speed;
	}
	tSprDragon->setFlipX(mIsRight);
	tSprDragon->setPosition(tVec);
	//tpNode->setPosition(ccpLerp(tpNode->getPosition(),tVec - Vec2(512, 160), dt));

}

bool HelloWorld::onTouchBegan(Touch * tTouch, Event * tEvnet)
{
	return true;
}

void HelloWorld::onTouchMoved(Touch * tTouch, Event * tEvnet)
{
	Vec3 tEye = mpCamera->getEye();

	tEye.x -= tTouch->getDelta().x*0.000000001;
	tEye.y -= tTouch->getDelta().y*0.000000001;

	mpCamera->setEye(tEye);
}

void HelloWorld::DoBackFlip()
{

	switch (mState)
	{
	case 0:
		mpSpr_0->setVisible(false);
		mpSpr_1->setVisible(true);

		break;
	case 1:
		mpSpr_0->setVisible(true);
		mpSpr_1->setVisible(false);
		break;
	}

	auto tSecondHalf = OrbitCamera::create(
		0.5f,
		1.0f, 0,
		270, 90.0f,
		0, 0);

	switch (mState)
	{
	case 0:
		mpSpr_0->runAction(tSecondHalf);
		break;
	case 1:
		mpSpr_1->runAction(tSecondHalf);
		break;

	}

}