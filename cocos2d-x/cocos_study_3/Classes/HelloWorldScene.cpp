#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TestScene2.h"
#include "TestScene3.h"

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
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	/*
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
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
	mpSprHello = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
	mpSprHello->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(mpSprHello, 0);
    
	//this->scheduleUpdate();
	//this->unscheduleUpdate();

	pt = ProgressTimer::create(mpSprHello);
	pt->setType(ProgressTimer::Type::RADIAL);
	pt->setPosition(Vec2(100,160));
	this->addChild(pt);


	this->schedule(schedule_selector(HelloWorld::callEveryFrame));
	this->schedule(schedule_selector(HelloWorld::myTick), 0.1f);
	this->scheduleOnce(schedule_selector(HelloWorld::myTickOnce), 3.0f);
	*/


	auto item1 = MenuItemFont::create(
		"pushScene",
		CC_CALLBACK_1(HelloWorld::doPushScene, this));
	item1->setColor(Color3B(0, 0, 0));

	auto item2 = MenuItemFont::create(
		"pushScene transition",
		CC_CALLBACK_1(HelloWorld::doPushSceneTran, this));
	item2->setColor(Color3B(0, 0, 0));

	auto item3 = MenuItemFont::create(
		"replaceScene",
		CC_CALLBACK_1(HelloWorld::doReplaceScene, this));
	item3->setColor(Color3B(0, 0, 0));

	auto item4 = MenuItemFont::create(
		"replaceScene transition",
		CC_CALLBACK_1(HelloWorld::doReplaceSceneTran, this));
	item4->setColor(Color3B(0, 0, 0));

	// 메뉴 생성
	auto pMenu = Menu::create(item1, item2, item3, item4, nullptr);

	// 메뉴 정렬
	pMenu->alignItemsVertically();

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);



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

void HelloWorld::doPushScene(Ref * pSender)
{
	// 두번째 장면
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(pScene);
}

void HelloWorld::doPushSceneTran(Ref * pSender)
{
	static int nIndex1 = 0;

	// 두번째 장면
	auto pScene = TestScene2::createScene();
	Director::getInstance()->pushScene(createTransition(nIndex1, 1, pScene));

	nIndex1++;
	if (nIndex1 > 40)
	{
		nIndex1 = 0;
	}
}

void HelloWorld::doReplaceScene(Ref * pSender)
{    // 세번째 장면
	auto pScene = TestScene3::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::doReplaceSceneTran(Ref * pSender)
{
	static int nIndex2 = 2;

	// 세번째 장면
	auto pScene = TestScene3::createScene();
	Director::getInstance()->replaceScene(createTransition(nIndex2, 1, pScene));

	nIndex2--;
	if (nIndex2 < 0)
	{
		nIndex2 = 40;
	}
}

cocos2d::TransitionScene * HelloWorld::createTransition(int nIndex, float t, cocos2d::Scene * s)
{
	Director::getInstance()->setDepthTest(false);

	switch (nIndex)
	{
		// 점프하면서 Zoom
	case 0: return TransitionJumpZoom::create(t, s);


		// 시계방향으로 침이 돌면서 장면이 바뀜
	case 1: return TransitionProgressRadialCCW::create(t, s);
		// 시계반대방향으로 침이 돌면서 장면이 바뀜
	case 2: return TransitionProgressRadialCW::create(t, s);
	case 3: return TransitionProgressHorizontal::create(t, s);
	case 4: return TransitionProgressVertical::create(t, s);
	case 5: return TransitionProgressInOut::create(t, s);
	case 6: return TransitionProgressOutIn::create(t, s);

		// 교차
	case 7: return TransitionCrossFade::create(t, s);


		// 페이지넘김형식 : PageTransitionForward
	case 8: return TransitionPageTurn::create(t, s, false);
		// 페이지넘김형식 : PageTransitionBackward
	case 9: return TransitionPageTurn::create(t, s, true);
		// 바둑판무늬 좌측하단부터 우측상단순으로 사라짐
	case 10: return TransitionFadeTR::create(t, s);
		// 바툭판무늬 우측상단부터 좌측하단순으로 사라짐
	case 11: return TransitionFadeBL::create(t, s);
		// 하단에서 상단으로 잘라냄
	case 12: return TransitionFadeUp::create(t, s);
		// 상단에서 하단으로 잘라냄
	case 13: return TransitionFadeDown::create(t, s);


		// 바둑판무늬 뿌리기
	case 14: return TransitionTurnOffTiles::create(t, s);


		// 가로로 세등분 나눔
	case 15: return TransitionSplitRows::create(t, s);
		// 세로로 세등분 나눔, 양끝의 두둥분은 밑으로 나머지는 위로
	case 16: return TransitionSplitCols::create(t, s);


		// 페이드인아웃 : 검정 화면
	case 17: return TransitionFade::create(t, s);
		// 페이드인아웃 : 하얀 화면
	case 18: return TransitionFade::create(t, s, Color3B::WHITE);


		// X축(횡선)을 기준으로 회전 : FlipXLeftOver
	case 19: return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 : FlipXRightOver
	case 20: return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYUpOver
	case 21: return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 : FlipYDownOver
	case 22: return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularLeftOver
	case 23: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 : FlipAngularRightOver
	case 24: return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXLeftOver
	case 25: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// X축(횡선)을 기준으로 회전 (확대) : ZoomFlipXRightOver
	case 26: return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYUpOver
	case 27: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		// Y축(종선)을 기준으로 회전 (확대) : ZoomFlipYDownOver
	case 28: return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularLeftOver
	case 29: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularRightOver
	case 30: return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);


		// 이전장면 수축 다음장면 확대
	case 31: return TransitionShrinkGrow::create(t, s);
		// 회전하면서 Zoom
	case 32: return TransitionRotoZoom::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 덮어씀
	case 33: return TransitionMoveInL::create(t, s);
		// 오른쪽에서 다음장면이 나타남
	case 34: return TransitionMoveInR::create(t, s);
		// 위쪽에서 다음장면이 나타남
	case 35: return TransitionMoveInT::create(t, s);
		// 아래쪽에서 다음장면이 나타남
	case 36: return TransitionMoveInB::create(t, s);


		// 왼쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 37: return TransitionSlideInL::create(t, s);
		// 오른쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 38: return TransitionSlideInR::create(t, s);
		// 위쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 39: return TransitionSlideInT::create(t, s);
		// 아래쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 40: return TransitionSlideInB::create(t, s);

	default: break;
	}

	return NULL;
}

void HelloWorld::update(float dt) 
{
	Vec2 vec = mpSprHello->getPosition();
	vec.x = vec.x + 100.0f * dt;
	vec.y = 100.0f;

	//mpSprHello->setPosition(ccpLerp(mpSprHello->getPosition(), vec, dt));
	mpSprHello->setPosition(vec);
}

void HelloWorld::myTick(float f)
{
	//log("tick");
}

void HelloWorld::callEveryFrame(float f)
{
	nNum++;
	this->SpriteProgressToRadial(nNum * 2);
	if (nNum > 50) {
		nNum = 0;
	}

	//log("fps..%d", nNum);
}

void HelloWorld::myTickOnce(float f)
{
	//log("tickOnce after delay");
}

void HelloWorld::SpriteProgressToRadial(float f)
{
	pt->setPercentage(f);

}










