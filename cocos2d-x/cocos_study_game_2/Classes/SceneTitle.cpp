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


	auto tMenuPlay = MenuItemFont::create("Play", [](Ref * pSender) 
	{
		auto tTransition = TransitionSplitRows::create(0.5, ScenePlay::createScene());
		Director::getInstance()->replaceScene(tTransition);
	});
	tMenuPlay->setPosition(Vec2(tCenter.x,tVSize.height * 0.45));
	
	auto tMenu = Menu::create(tMenuPlay, nullptr);
	tMenu->setAnchorPoint(Vec2::ZERO);
	tMenu->setPosition(Vec2::ZERO);
	tUILayer->addChild(tMenu);

	

#pragma region Bg

	auto tBgLayer = Layer::create();
	tBgLayer->setZOrder(0);
	this->addChild(tBgLayer);
	
	auto tCache = SpriteFrameCache::getInstance();
	tCache->addSpriteFramesWithFile("bg.plist","bg.png");

	auto tBg_0 = Sprite::createWithSpriteFrameName("bg_top_0.png");
	tBg_0->setScale(1.8, 2);
	tBg_0->setRotation(-90);
	tBg_0->setZOrder(0);
	tBg_0->setPosition(Vec2(tVSize.width * 0.5, tVSize.height * 0.7));
	tBgLayer->addChild(tBg_0);
	auto tBg_1 = Sprite::createWithSpriteFrameName("bg_top_1.png");
	tBg_1->setScale(1.8, 2);
	tBg_1->setRotation(-90);
	tBg_1->setZOrder(1);
	tBg_1->setPosition(Vec2(tVSize.width * 0.5, tVSize.height * 0.2));
	tBgLayer->addChild(tBg_1);

#pragma endregion
	return true;
}
