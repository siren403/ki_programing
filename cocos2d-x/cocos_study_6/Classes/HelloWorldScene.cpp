#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SoundMgr.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE        "Sounds/effect2.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE        "Sounds/effect1.raw"
#else
#define EFFECT_FILE        "Sounds/effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE        "Sounds/music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#define MUSIC_FILE        "Sounds/background.ogg"
#else
#define MUSIC_FILE        "Sounds/background.mp3"
#endif // CC_PLATFORM_WIN32

std::string menuItems[] = {
	"play background music",
	"pause background music",
	"resume background music",
	"stop background music",
	"play effect",
	"play effect repeatly",
	"pause effect",
	"resume effect",
	"stop effect",
};

USING_NS_CC;
using namespace CocosDenshion;


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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//// 메뉴 아이템 생성 및 초기화

	//auto pMenu = Menu::create();

	//int nMenuCount = sizeof(menuItems) / sizeof(menuItems[0]);

	//for (int i = 0; i < nMenuCount; ++i)
	//{
	//	auto label = Label::createWithTTF(menuItems[i].c_str(), "fonts/arial.ttf", 24);
	//	label->setColor(Color3B(0, 0, 0));
	//	auto pMenuItem = MenuItemLabel::create(
	//		label,
	//		CC_CALLBACK_1(HelloWorld::doSoundAction, this));
	//	pMenu->addChild(pMenuItem, i + 10000);
	//}

	//// 메뉴 정렬
	//pMenu->alignItemsVertically();

	//// 레이어에 메뉴 객체 추가
	//this->addChild(pMenu);


	//// preload background music and effect
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	//SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FILE);

	//// set default volume
	//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	/*
	SoundMgr::getInstance()->create();

	SoundMgr::getInstance()->playBGM(0);
	SoundMgr::getInstance()->playEffect(0);
*/
	mScrollSpeed = 40.0f;

	mSpriteA = Sprite::create("bg.png");
	mSpriteA->setAnchorPoint(Vec2(0.0, 0.0));
	this->addChild(mSpriteA, 0);

	Vec2 tVecA;
	tVecA.x = 0.0f;
	tVecA.y = 0.0f;
	mSpriteA->setPosition(tVecA);


	mSpriteB = Sprite::create("bg.png");
	mSpriteB->setAnchorPoint(Vec2(0.0, 0.0));
	this->addChild(mSpriteB, 0);

	Vec2 tVecB;
	tVecB.x = 0.0;
	tVecB.y = mSpriteA->getContentSize().height;
	mSpriteB->setPosition(tVecB);


	/*ActionInterval * tAction = MoveBy::create(4, Vec2(0, -800));

	auto tSequence = Sequence::create(
		tAction,
		CallFunc::create([tSpriteA, tSpriteB]()
	{
	
		if (tSpriteA->getPositionY() <= -800)
		{
			tSpriteA->setPositionY(800);
		}

		if (tSpriteB->getPositionY() <= -800)
		{
			tSpriteB->setPositionY(800);
		}
	}),
		nullptr
	);

	RepeatForever * tRepeat = RepeatForever::create(tSequence);
	tSpriteA->runAction(tRepeat);
	tSpriteB->runAction(tRepeat->clone());*/

	this->scheduleUpdate();


	LoadFromFile();

	auto tKeyboard = EventListenerKeyboard::create();
	tKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event * event) 
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_Q:
			mPlayInfo.mName = "pokpoongryu";

			mPlayInfo.mScore = mPlayInfo.mScore + 1;
			mPlayInfo.mX = 240.0f;
			mPlayInfo.mY = 160.0f;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			LoadFromFile();
			break;
		case EventKeyboard::KeyCode::KEY_E:
			SaveToFile();
			break;
		case EventKeyboard::KeyCode::KEY_R:
			DisplayPlayInfo();
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyboard,this);


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

void HelloWorld::onExit()
{

	//SoundMgr::getInstance()->destroy();

/*
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	SimpleAudioEngine::end();*/

	Layer::onExit();
}

void HelloWorld::doSoundAction(Ref* pSender)
{
	auto pMenuItem = (MenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;

	switch (nIdx)
	{
		// play background music
	case 0:
		SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
		break;
		// pause background music : 윈도우에선 동작 안함
	case 1:
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		break;
		// resume background music : 윈도우에선 동작 안함
	case 2:
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		break;
		// stop background music
	case 3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		break;
		// play effect
	case 4:
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE);
		break;
		// play effect
	case 5:
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE, true);
		break;
		// pause effect
	case 6:
		SimpleAudioEngine::getInstance()->pauseEffect(m_nSoundId);
		break;
		// resume effect
	case 7:
		SimpleAudioEngine::getInstance()->resumeEffect(m_nSoundId);
		break;
		// stop effect
	case 8:
		SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId);
		break;

	}

}

void HelloWorld::update(float dt)
{
	mVecA.y = mVecA.y - mScrollSpeed*dt;
	mSpriteA->setPosition(mVecA);

	//mVecB.x = 0.0f;
	mVecB.y = mVecB.y - mScrollSpeed*dt;
	mSpriteB->setPosition(mVecB);

	//float tHeight = mpSpriteA->getContentSize().height;

	if (mVecA.y <= -800)
	{
		mVecA.y = 800;
	}

	if (mVecB.y <= -800)
	{
		mVecB.y = 800;
	}


}

void HelloWorld::LoadFromFile()
{
	mPlayInfo.mName = UserDefault::getInstance()->getStringForKey("key_name");

	mPlayInfo.mScore = UserDefault::getInstance()->getIntegerForKey("key_score");
	mPlayInfo.mX = UserDefault::getInstance()->getFloatForKey("key_x");
	mPlayInfo.mY = UserDefault::getInstance()->getFloatForKey("key_y");

	DisplayPlayInfo();

}

void HelloWorld::SaveToFile()
{
	UserDefault::getInstance()->setStringForKey("key_name", mPlayInfo.mName);

	UserDefault::getInstance()->setIntegerForKey("key_score", mPlayInfo.mScore);
	UserDefault::getInstance()->setFloatForKey("key_x", mPlayInfo.mX);
	UserDefault::getInstance()->setFloatForKey("key_y", mPlayInfo.mY);

	UserDefault::getInstance()->flush();
}

void HelloWorld::DisplayPlayInfo()
{
	string tString = "";

	char tszTemp[256];
	memset(tszTemp, 0, 256);
	sprintf(tszTemp, "%s, %d, %f, %f ",
		mPlayInfo.mName.c_str(),
		mPlayInfo.mScore,
		mPlayInfo.mX,
		mPlayInfo.mY);

	tString = tString + tszTemp;

	log(tString.c_str());
}
