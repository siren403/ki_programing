#include "SceneTitle.h"
#include "ScenePlay.h"

Scene * SceneTitle::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneTitle::create();
	scene->addChild(layer);
	return scene;
}

bool SceneTitle::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto tVSize = Director::getInstance()->getVisibleSize();
	auto tCenter = Vec2(tVSize.width*0.5, tVSize.height*0.5);

	auto tUILayer = Layer::create();
	tUILayer->setAnchorPoint(Vec2::ZERO);
	tUILayer->setPosition(Vec2::ZERO);
	tUILayer->setZOrder(10);
	this->addChild(tUILayer);


	auto tMenuPlay = MenuItemFont::create("시작",[](Ref * pSender) 
	{
		auto tTransition = TransitionSplitRows::create(0.5, ScenePlay::createScene());
		Director::getInstance()->replaceScene(tTransition);
	});
	tMenuPlay->setPosition(Vec2(tVSize.width * 0.9,tVSize.height * 0.1));
	
	auto tMenu = Menu::create(tMenuPlay, nullptr);
	tMenu->setAnchorPoint(Vec2::ZERO);
	tMenu->setPosition(Vec2::ZERO);
	tUILayer->addChild(tMenu);

	auto tTestLabel = Label::createWithTTF(
		"한글 테스트.... 가나다라마바사쯍듉긁궳",
		"fonts/NanumGothic.ttf",
		32
	);
	tTestLabel->setPosition(tVSize.width / 2, tVSize.height *0.5);

	this->addChild(tTestLabel,1);
	tTestLabel = Label::createWithTTF(
		"한글 테스트.... 가나다라마바사쯍듉긁궳",
		"fonts/BMJUA_ttf.ttf",
		32
	);
	tTestLabel->setPosition(tVSize.width / 2, tVSize.height * 0.4);
	this->addChild(tTestLabel, 1);

#pragma region Bg

	auto tBgLayer = Layer::create();
	tBgLayer->setZOrder(0);
	this->addChild(tBgLayer);
	

	auto tBg = Sprite::create("bg_top.png");
	tBg->setScale(1.8);
	tBg->setAnchorPoint(Vec2(0, 1));
	tBg->setZOrder(0);
	tBg->setPosition(Vec2(0, tVSize.height));
	tBgLayer->addChild(tBg);
	tBg = Sprite::create("bg_bot.png");
	tBg->setScale(1.6);
	tBg->setAnchorPoint(Vec2(0, 0));
	tBg->setZOrder(1);
	tBg->setPosition(Vec2(0, 0));
	tBgLayer->addChild(tBg);
	auto tBg_0 = Sprite::create("bg_bot.png");
	tBg_0->setScale(1.6);
	tBg_0->setAnchorPoint(Vec2(0, 0));
	tBg_0->setZOrder(1);
	tBg_0->setPosition(Vec2(tBg->getContentSize().width, 0));
	tBgLayer->addChild(tBg_0);
#pragma endregion
	return true;
}
