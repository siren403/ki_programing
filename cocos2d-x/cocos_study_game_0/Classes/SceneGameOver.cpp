#include "SceneGameOver.h"
#include "SceneTitle.h"



Scene * SceneGameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneGameOver::create();
	scene->addChild(layer);
	return scene;
}

bool SceneGameOver::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto tVisibleSize = Director::getInstance()->getVisibleSize();
	auto tCenter = Vec2(tVisibleSize.width / 2, tVisibleSize.height / 2);

	auto tLabelTitle = Label::create("End", "fonts/arial.ttf", 40);
	tLabelTitle->setColor(Color3B::BLACK);

	tLabelTitle->setPosition(tCenter);
	this->addChild(tLabelTitle, 1);

	auto tMenuNextScene = MenuItemFont::create(
		"Next",
		CC_CALLBACK_0(SceneGameOver::NextScene, this)
	);
	tMenuNextScene->setColor(Color3B::BLACK);
	tMenuNextScene->setPosition(Vec2(tCenter.x, tCenter.y *0.2f));

	auto tMenu = Menu::create(tMenuNextScene, nullptr);
	tMenu->setPosition(Vec2::ZERO);

	this->addChild(tMenu, 10);
	return true;
}

void SceneGameOver::NextScene()
{
	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(1, SceneTitle::createScene())
	);
}