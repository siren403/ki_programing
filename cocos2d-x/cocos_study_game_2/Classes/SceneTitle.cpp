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


	auto tMenuPlay = MenuItemFont::create("Title", [](Ref * pSender) 
	{
		auto tTransition = TransitionSplitRows::create(0.5, ScenePlay::createScene());
		Director::getInstance()->replaceScene(tTransition);
	});
	tMenuPlay->setPosition(Vec2(tCenter.x,tVSize.height * 0.45));
	
	auto tMenu = Menu::create(tMenuPlay, nullptr);
	tMenu->setAnchorPoint(Vec2::ZERO);
	tMenu->setPosition(Vec2::ZERO);
	tUILayer->addChild(tMenu);



	auto tLabel = Label::create("Title", "fonts/arial.ttf", 30);
	tLabel->setPosition(Vec2(tVSize.width*0.5, tVSize.height*0.6));
	tLabel->setZOrder(10);
	this->addChild(tLabel);


	




	return true;
}
