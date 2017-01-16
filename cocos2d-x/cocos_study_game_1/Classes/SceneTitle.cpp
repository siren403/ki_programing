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

	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto tVisibleSize = Director::getInstance()->getVisibleSize();

#pragma region UI
	auto tUILayer = Layer::create();
	this->addChild(tUILayer, 10);

	auto tLabelTitle = Label::create(
		"TITLE",
		"fonts/arial.ttf",
		30
	);
	tLabelTitle->setPosition(Vec2(tVisibleSize.width*0.5f, tVisibleSize.height * 0.65f));
	tUILayer->addChild(tLabelTitle, 0);

	auto tMenuPlay = MenuItemFont::create(
		"Play",
		[](Ref * pSender)
	{
		auto tTransition = TransitionSplitRows::create(1, ScenePlay::createScene());
		Director::getInstance()->replaceScene(tTransition);
	}
	);
	tMenuPlay->setPosition(Vec2(tVisibleSize.width*0.5f, tVisibleSize.height * 0.35f));
	auto tMenu = Menu::create(
		tMenuPlay,
		nullptr
	);
	tMenu->setPosition(Vec2::ZERO);
	tUILayer->addChild(tMenu, 0);
#pragma endregion

#pragma region Ghost


	mpParall = ParallaxNode::create();
	this->addChild(mpParall, 0);

	auto tBackground = Sprite::create("background.png");
	tBackground->setAnchorPoint(Vec2(0, 0));
	mpParall->addChild(tBackground, 0, Vec2(1, 0), Vec2(0, -100));

	auto tGhost = Sprite::create("ghost.png");
	tGhost->setScale(0.5);
	mpParall->addChild(tGhost, 1, Vec2(2, 0), Vec2(100, 100));

	tGhost = Sprite::create("ghost.png");
	tGhost->setScale(0.3);
	mpParall->addChild(tGhost, 1, Vec2(2.3, 0), Vec2(200, 250));

	tGhost = Sprite::create("ghost.png");
	tGhost->setScale(0.34);
	tGhost->setFlipX(true);
	mpParall->addChild(tGhost, 1, Vec2(1.5, 0), Vec2(340, 200));

	tGhost = Sprite::create("ghost.png");
	tGhost->setScale(0.45);
	tGhost->setFlipX(true);
	mpParall->addChild(tGhost, 1, Vec2(1.8, 0), Vec2(480, 150));

	tGhost = Sprite::create("ghost.png");
	tGhost->setScale(0.4);
	tGhost->setFlipX(true);
	mpParall->addChild(tGhost, 1, Vec2(1.6, 0), Vec2(600, 100));

#pragma endregion

	auto go = MoveBy::create(4, Vec2(-160, -100.0f));
	auto goBack = go->reverse();
	auto tSequence = Sequence::create(go, goBack, nullptr);
	auto tRepeatForever = RepeatForever::create(tSequence);
	mpParall->runAction(tRepeatForever);

	return true;
}
