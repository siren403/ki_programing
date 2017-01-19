#include "ScenePlay.h"
#include "CActor.h"
#include "CEnemyFactory.h"
#include "SimpleAudioEngine.h"
#include "SceneTitle.h"

#define ZORDER_ACTOR 6
#define ZORDER_BULLET_LAYER 10
#define ZORDER_ENEMY 5

using namespace CocosDenshion;

Scene * ScenePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = ScenePlay::create();
	scene->addChild(layer);
	return scene;
}

bool ScenePlay::init()
{
	if(!LayerColor::initWithColor(Color4B::WHITE))
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

	mEnemy = CEnemyFactory::createBossSample(tBulletLayer);
	mEnemy->setPosition(Vec2(tVSize.width, tVSize.height * 1.5));
	mEnemy->setZOrder(ZORDER_ENEMY);
	this->addChild(mEnemy);


	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("warnig.mp3");

	float tTintTime = 0.5;
	auto tSeqStart = Sequence::create(
		DelayTime::create(1),
		CallFunc::create([]() 
	{ 
		SimpleAudioEngine::getInstance()->playEffect("warnig.mp3");
	}),
		DelayTime::create(0.33),
		TintTo::create(tTintTime,Color3B::RED),
		TintTo::create(tTintTime, Color3B::WHITE),
		TintTo::create(tTintTime, Color3B::RED),
		TintTo::create(tTintTime, Color3B::WHITE),
		TintTo::create(tTintTime, Color3B::RED),
		TintTo::create(tTintTime, Color3B::WHITE),
		DelayTime::create(1),
		CallFunc::create([this,tVSize]()
	{
		Vec2 tVec = Vec2(tVSize.width * 0.75, tVSize.height * 0.28);
		this->mEnemy->runAction(
			EaseExponentialOut::create(
				MoveTo::create(0.3, tVec)
			)
		);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3");
	}),
		DelayTime::create(1),
		CallFunc::create([this]() 
	{ 
		this->mActor->setIsControl(true); 
		this->mEnemy->setState(CEnemy::STATE_ATTACK);
	}),
		nullptr
	);
	this->runAction(tSeqStart);


	this->scheduleUpdate();
	return true;
}

void ScenePlay::update(float dt)
{
	if (mActor->getIsControl())
	{
		mActor->checkCollisionByEnemy(mEnemy);

		mEnemy->checkCollisionToActor(mActor);
	}
	if (mActor->getIsAlive() == false)
	{
		this->unscheduleUpdate();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto tSeqEnd = Sequence::create(
			TintTo::create(1,Color3B::BLACK),
			CallFunc::create([this]()
		{
			Director::getInstance()->replaceScene(
				TransitionFade::create(1,SceneTitle::createScene())
			);
		}),
			nullptr
		);
		this->runAction(tSeqEnd);
		log("end");
	}
	if (mEnemy->getIsAlive() == false)
	{
		mActor->setIsControl(false);
		this->unscheduleUpdate();
		float tTintTime = 0.4;
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto tSeqEnd = Sequence::create(
			TintTo::create(tTintTime, Color3B::GREEN),
			TintTo::create(tTintTime, Color3B::WHITE),
			TintTo::create(tTintTime, Color3B::GREEN),
			TintTo::create(tTintTime, Color3B::WHITE),
			TintTo::create(tTintTime, Color3B::GREEN),
			TintTo::create(tTintTime, Color3B::WHITE),
			CallFunc::create([this]()
		{
			Director::getInstance()->replaceScene(
				TransitionFade::create(1, SceneTitle::createScene())
			);
		}),
			nullptr
			);
		this->runAction(tSeqEnd);
		log("end");
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
