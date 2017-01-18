#include "ScenePlay.h"
#include "CActor.h"
#include "CTime.h"

#define ZORDER_BULLET 10

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

	auto tBulletLayer = Layer::create();
	tBulletLayer->setZOrder(ZORDER_BULLET);
	this->addChild(tBulletLayer);


	auto tActor = CActor::create(tBulletLayer);
	tActor->setPosition(Vec2(tVSize.width*0.5, tVSize.height*0.5));
	this->addChild(tActor);




	return true;
}

void ScenePlay::onEnter()
{
	Layer::onEnter();

	auto tKeyboard = EventListenerKeyboard::create();
	tKeyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event * event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyboard, this);
}

void ScenePlay::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	Layer::onExit();
}
