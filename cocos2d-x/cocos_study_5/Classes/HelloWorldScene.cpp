#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CGrid.h"
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

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	mplblTest = Label::createWithTTF("UI", "fonts/Marker Felt.ttf", 18);
	mplblTest->setColor(Color3B::RED);
	mplblTest->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - mplblTest->getContentSize().height));

	this->addChild(mplblTest, 1);


	/*mpListener = EventListenerTouchOneByOne::create();

	mpListener->setSwallowTouches(true);

	mpListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	mpListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	mpListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);*/
	////그리드 맵 생성.
	/*mpGrid = new CGrid();
	mpGrid->Create();
	mpGrid->SetScene(this);

	mpGrid->Build();*/
    
	auto tSprCoin = Sprite::create("coin.png");
	tSprCoin->setScale(0.4f);
	tSprCoin->setAnchorPoint(Vec2::ZERO);

	auto tMap = TMXTiledMap::create("scroll.tmx");
	//this->addChild(tMap, 0, 11);
	tMap->setAnchorPoint(Vec2(0.0f, 0.0f));

	/*TMXObjectGroup *tObj = tMap->getObjectGroup("Object Layer 1");
	ValueMap tSpawnPositionActor = tObj->getObject("actor");

	int tX = tSpawnPositionActor["x"].asInt();
	int tY = tSpawnPositionActor["y"].asInt();

	Vec2 tVec;
	tVec.x = tX;
	tVec.y = tY;
	tSprCoin->setPosition(tVec);
	tMap->addChild(tSprCoin);


	int tRow = 0;
	int tCol = 0;
	for (tRow = 0; tRow<10; tRow++)
	{
		for (tCol = 0; tCol<15; tCol++)
		{
			int tGID = tMap->getLayer("Tile Layer 1")->getTileGIDAt(Vec2(tCol, tRow));
			Value tValue = tMap->getPropertiesForGID(tGID);


			if (false == tValue.isNull())
			{
				int tAttrib = tValue.asValueMap()["mAttrib"].asInt();

				log("tAttrib: %d", tAttrib);
			}

		}
	}*/
	
	ParallaxNode *tpNode = ParallaxNode::create();
	this->addChild(tpNode);
	tpNode->addChild(tMap, 0, Vec2(0.0f, 1.0f), Vec2(0, 0));


	auto go = MoveBy::create(4, Vec2(0, -960 + 320));
	auto goBack = go->reverse();
	auto tSequence = Sequence::create(go, goBack, NULL);
	auto tRepeatForever = RepeatForever::create(tSequence);
	tpNode->runAction(tRepeatForever);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

	//mpGrid->UnBuild();


	//if (NULL != mpGrid)
	//{
	//	mpGrid->Destroy();

	//	delete mpGrid;
	//	mpGrid = NULL;
	//}

	////터치 이벤트 등록해지
	//_eventDispatcher->removeEventListener(mpListener);

    //Close the cocos2d-x game scene and quit the application


    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto tTouchPos = touch->getLocation();


	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto tTouchPos = touch->getLocation();
}


void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto tTouchPos = touch->getLocation();

	//log("%f, %f", tTouchPos.x, tTouchPos.y);



	float tX = tTouchPos.x;
	float tY = tTouchPos.y;

	//y축이 반대인 것을 고려
	tY = 320 - tY;

	//타일격자 단위의 숫자로 변환
	int tCol = 0;
	int tRow = 0;

	tCol = tX / 80;
	tRow = tY / 80;


	int tAttrib = 0;
	tAttrib = mpGrid->GetAttrib(tCol, tRow);

	//아예 터치좌표를 매개변수로 받아서 결정하도록 할수도 있음.: 실습: 그러한 멤버 함수도 하나 만들어볼 것.


	char tszTemp[512];
	memset(tszTemp, 0, 512);
	sprintf(tszTemp, "tCol: %d, tRow: %d, attrib: %d", tCol, tRow, tAttrib);
	mplblTest->setString(tszTemp);
}
void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//전화가 오는 경우 등을 처리하면 된다.
}
