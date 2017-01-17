#include "ScenePlay.h"

Scene * ScenePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = ScenePlay::create();
	scene->addChild(layer);
	return scene;
}

bool ScenePlay::init()
{
	if(!Layer::init())
	{
		return false;
	}

	auto tVSize = Director::getInstance()->getVisibleSize();

	auto tLabel = Label::create("Play", "fonts/arial.ttf", 50);
	tLabel->setPosition(Vec2(tVSize.width*0.5, tVSize.height*0.5));
	this->addChild(tLabel);

	return true;
}
