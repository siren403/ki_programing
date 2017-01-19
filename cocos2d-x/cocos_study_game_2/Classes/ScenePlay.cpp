#include "ScenePlay.h"
#include "CActor.h"
#include "CEnemyFactory.h"

#define ZORDER_ACTOR 6
#define ZORDER_BULLET_LAYER 10
#define ZORDER_ENEMY 5

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
	tBulletLayer->setZOrder(ZORDER_BULLET_LAYER);
	this->addChild(tBulletLayer);

	mActor = CActor::create(tBulletLayer);
	mActor->setZOrder(ZORDER_ACTOR);
	mActor->setPosition(Vec2(tVSize.width*0.3, tVSize.height*0.5));
	this->addChild(mActor);

	auto tSeqStart = Sequence::create(
		DelayTime::create(1),
		CallFunc::create([this]() { mActor->setIsControl(true); }),
		nullptr
	);
	this->runAction(tSeqStart);


	mEnemy = CEnemyFactory::createBossSample(tBulletLayer);
	mEnemy->setPosition(Vec2(tVSize.width * 0.8, tVSize.height * 0.5));
	mEnemy->setZOrder(ZORDER_ENEMY);
	this->addChild(mEnemy);



	this->scheduleUpdate();
	return true;
}

void ScenePlay::update(float dt)
{
	if (mActor->getIsControl())
	{
		mActor->checkCollisionByEnemy(mEnemy);
	}
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
