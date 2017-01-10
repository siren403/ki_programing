#include "exam_ease.h"

USING_NS_CC;



void ExamEase::DoActionReset()
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

Scene* ExamEase::createScene()
{
	auto scene = Scene::create();

	auto layer = ExamEase::create();

	scene->addChild(layer);

	return scene;
}

bool ExamEase::Init()
{
	if (!Layer::init())
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
		CC_CALLBACK_1(ExamEase::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto pMenuClose = Menu::create(closeItem, nullptr);
	this->addChild(pMenuClose);

	MenuItemFont::setFontSize(14);
	// 메뉴 아이템 생성 및 초기화

	auto pMenuItem = MenuItemFont::create(
		"DoAction",
		CC_CALLBACK_1(ExamEase::DoAction, this));
	pMenuItem->setColor(Color3B(255, 255, 0));
	// 메뉴 생성
	auto pMenu = Menu::create(pMenuItem, nullptr);
	// 메뉴 위치 지정
	pMenu->setPosition(Vec2(240, 50));
	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);


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

void ExamEase::menuCloseCallback(Ref * pSender)
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
}

void ExamEase::DoAction(Ref * pSender)
{
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
		mpEaseIn = EaseElasticIn::create(static_cast<ActionInterval *>(mpMove), 0.4f);
		mpEaseOut = EaseElasticOut::create(static_cast<ActionInterval *>(mpMove), 0.4f);
		mpEaseInOut_1 = EaseElasticInOut::create(static_cast<ActionInterval *>(mpMove), 0.4f);
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
