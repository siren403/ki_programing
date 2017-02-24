#include "SceneFont.h"

Scene * SceneFont::createScene()
{
	auto scene = Scene::create();
	scene->addChild(SceneFont::create());
	return scene;
}

bool SceneFont::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::createWithTTF("hello world 한글", "NanumBarunGothicBold.ttf", 28);

	this->addChild(label);

	return true;
}
