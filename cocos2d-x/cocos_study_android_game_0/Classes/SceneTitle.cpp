#include "SceneTitle.h"
#include "ScenePlay.h"

Scene * SceneTitle::createScene()
{
	auto scene = Scene::create();
	auto title = SceneTitle::create();
	scene->addChild(title);
	return scene;
}

bool SceneTitle::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centerPos = Vec2(visibleSize.width, visibleSize.height);

	auto labelTitle = Label::create("Title", "fonts/arial.ttf", 64);
	labelTitle->setPosition(visibleSize.width*0.5, visibleSize.height*0.8);
	this->addChild(labelTitle, 1);


	auto btnNextScene = MenuItemFont::create("Play", [](Ref * sender) 
	{
		Director::getInstance()->replaceScene(
			TransitionFade::create(0.3, ScenePlay::createScene())
		);
	});

	btnNextScene->setPosition(Vec2(0, 0));
	auto menuUI = Menu::create(btnNextScene, nullptr);
	menuUI->setPosition(visibleSize.width*0.5, visibleSize.height*0.4);
	this->addChild(menuUI, 10);

	return true;
}

void SceneTitle::onEnter()
{
	LayerColor::onEnter();



}

void SceneTitle::onExit()
{


	LayerColor::onExit();
}
