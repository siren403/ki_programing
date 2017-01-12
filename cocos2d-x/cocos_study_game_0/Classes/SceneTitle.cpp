#include "SceneTitle.h"
#include "SceneField.h"


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
	auto tCenter = Vec2(tVisibleSize.width / 2, tVisibleSize.height / 2);
	
	/*auto tLabelTitle = Label::create("Title", "fonts/arial.ttf", 40);
	tLabelTitle->setColor(Color3B::BLACK);
*/
	auto tLabelTitle = LabelBMFont::create("TITLE", "fonts/west_england-64.fnt");
	tLabelTitle->setPosition(Vec2(tCenter.x,tVisibleSize.height * 0.55f));
	this->addChild(tLabelTitle, 1);


	auto tMenuNextScene = MenuItemFont::create(
		"Next",
		CC_CALLBACK_0(SceneTitle::NextScene, this)
	);
	tMenuNextScene->setColor(Color3B::BLACK);
	tMenuNextScene->setPosition(Vec2(tCenter.x, tCenter.y *0.35f));
	auto tSeqNext =
		RepeatForever::create(
			Sequence::create(
				EaseExponentialIn::create(ScaleTo::create(0.8f, 1.2f)),
				//DelayTime::create(0.03f),
				EaseExponentialOut::create(ScaleTo::create(0.3f, 1)),
				DelayTime::create(0.2f),
				nullptr
			)
		);
	tMenuNextScene->runAction(tSeqNext);


	auto tMenu = Menu::create(tMenuNextScene, nullptr);
	tMenu->setPosition(Vec2::ZERO);
	this->addChild(tMenu, 10);

	return true;
}


void SceneTitle::NextScene()
{
	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(1,SceneField::createScene())
	);
}