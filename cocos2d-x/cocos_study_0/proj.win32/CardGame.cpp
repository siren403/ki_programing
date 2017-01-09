#include "CardGame.h"
#include "SimpleAudioEngine.h"
#include <time.h>
#include <stdlib.h>
USING_NS_CC;

cocos2d::Scene * CCardGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CCardGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CCardGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	srand(time(NULL));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CCardGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto tMenuItem_1 = MenuItemFont::create("1", CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_1->setTag(1);
	tMenuItem_1->setPosition(Vec2((this->getContentSize().width / 2) - 50, 50));

	auto tMenuItem_2 = MenuItemFont::create("2", CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_2->setTag(2);
	tMenuItem_2->setPosition(Vec2((this->getContentSize().width / 2), 50));

	auto tMenuItem_3 = MenuItemFont::create("3", CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_3->setTag(3);
	tMenuItem_3->setPosition(Vec2((this->getContentSize().width / 2) + 50, 50));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, tMenuItem_1, tMenuItem_2, tMenuItem_3, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 10);


	mLeftLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	mLeftLabel->retain();
	mLeftLabel->setPosition(Vec2(100, 160));
	this->addChild(mLeftLabel);

	mRightLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	mRightLabel->retain();
	mRightLabel->setPosition(Vec2(400, 160));
	this->addChild(mRightLabel);



	mResultLabel = Label::createWithTTF("Result", "fonts/Marker Felt.ttf", 24);
	mResultLabel->retain();
	mResultLabel->setPosition(Vec2((this->getContentSize().width / 2), 100));
	this->addChild(mResultLabel);
	






	return true;
}

void CCardGame::menuCloseCallback(cocos2d::Ref * pSender)
{
	this->removeChild(mLeftLabel);
	if (NULL != mLeftLabel)
	{
		mLeftLabel->release();
		mLeftLabel = NULL;
	}

	this->removeChild(mRightLabel);
	if (NULL != mRightLabel)
	{
		mRightLabel->release();
		mRightLabel = NULL;
	}



	this->removeChild(mResultLabel);
	if (NULL != mResultLabel)
	{
		mResultLabel->release();
		mResultLabel = NULL;
	}


	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CCardGame::DoAction(Ref * pSender)
{
	auto tPressMenu = (MenuItem *)pSender;

	int tPlayer = tPressMenu->getTag();

	int tEnemy = rand() % 3 + 1;
	std::string tResult;

	mLeftLabel->setString(std::to_string(tPlayer));
	mRightLabel->setString(std::to_string(tEnemy));

	switch (tPlayer)
	{
	case 1://가위,sprite-3-0.png
		switch (tEnemy)
		{
		case 1:
			
			tResult = "Draw";
			break;
		case 2:
			tResult = "Lose";
			break;
		case 3:
			tResult = "Win";
			break;
		}
		break;
	case 2://바위,sprite-7-0.png
		switch (tEnemy)
		{
		case 1:
			tResult = "Win";
			break;
		case 2:
			tResult = "Draw";
			break;
		case 3:
			tResult = "Lose";
			break;
		}
		break;
	case 3://보,sprite-0-0.png
		switch (tEnemy)
		{
		case 1:
			tResult = "Lose";
			break;
		case 2:
			tResult = "Win";
			break;
		case 3:
			tResult = "Draw";
			break;
		}
		break;
	}

	mResultLabel->setString(tResult);

}
