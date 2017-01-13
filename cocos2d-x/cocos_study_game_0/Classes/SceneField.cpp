#include "SceneField.h"
#include "SceneGameOver.h"
#include "SpriteAnimator.h"
#include "Dice.h"

Scene * SceneField::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneField::create();
	scene->addChild(layer);
	return scene;
}

bool SceneField::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto tVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 tCenter = Vec2(tVisibleSize.width / 2, tVisibleSize.height / 2);

#pragma region create Player


	mpPlayerAnimator = SpriteAnimator::create("grossini_dance", 1, 14, 0.3f);
	mpPlayerAnimator->setPosition(Vec2(100, 200));
	mpPlayerAnimator->setAnchorPoint(Vec2(0.5, 0));
	mpPlayerAnimator->runAni();
	this->addChild(mpPlayerAnimator);


#pragma endregion

#pragma region InitBattleLayer

	mpBattleLayer = Layer::create();
	mpBattleLayer->setVisible(false);
	this->addChild(mpBattleLayer, 1);


	//==========================================
	mpSlimeLayer = Layer::create();
	mpBattleLayer->addChild(mpSlimeLayer, 1);


	mpSlimeSprite = Sprite::create("images/slime.png");
	mpSlimeSprite->setAnchorPoint(Vec2(0.5, 0));
	mpSlimeSprite->setPosition(Vec2(400, 160));
	mpSlimeSprite->setFlipX(true);
	mpSlimeLayer->addChild(mpSlimeSprite, 1);
	mSlimeHp = mSlimeMaxHp;

	auto tSlimeMotion = RepeatForever::create(
		Sequence::create(
			Spawn::create
			(
				ScaleTo::create(0.4, 1.2, 1),
				Sequence::create(
					DelayTime::create(0.1),
					ScaleTo::create(0.4, 1, 1.1),
					NULL
				),
				NULL
			),
			ScaleTo::create(0.4, 1, 1),
			NULL
		)
	);
	mpSlimeSprite->runAction(tSlimeMotion->clone());


	mpSlimeHpSprite = Sprite::create("images/white-512x512.png");
	mpSlimeHpSprite->setColor(Color3B::RED);
	mpSlimeHpSprite->setTextureRect(Rect(0, 0, 80, 5));
	mpSlimeHpSprite->setAnchorPoint(Vec2(0, 0.5f));
	mpSlimeHpSprite->setPosition(Vec2(mpSlimeSprite->getPosition().x-30, mpSlimeSprite->getPosition().y + 100));
	mpSlimeLayer->addChild(mpSlimeHpSprite);



	mpDice = Dice::create();
	mpDice->setPosition(Vec2(tCenter.x, tVisibleSize.height*0.5f));
	mpSlimeLayer->addChild(mpDice);


	//=========================================
#pragma endregion


#pragma region InitBattleLayer

	mpBossLayer = Layer::create();
	mpBossLayer->setVisible(false);
	mpBattleLayer->addChild(mpBossLayer, 2);

	auto tMenuItem_1 = MenuItemImage::create(
		"images/sprite-1.png",
		"images/sprite-1.png",
		CC_CALLBACK_1(SceneField::doAction, this));
	tMenuItem_1->setTag(1);
	tMenuItem_1->setPosition(Vec2((this->getContentSize().width / 2) - 50, 50));

	auto tMenuItem_2 = MenuItemImage::create(
		"images/sprite-2.png",
		"images/sprite-2.png",
		CC_CALLBACK_1(SceneField::doAction, this));
	tMenuItem_2->setTag(2);
	tMenuItem_2->setPosition(Vec2((this->getContentSize().width / 2), 50));

	auto tMenuItem_3 = MenuItemImage::create(
		"images/sprite-3.png",
		"images/sprite-3.png",
		CC_CALLBACK_1(SceneField::doAction, this));
	tMenuItem_3->setTag(3);
	tMenuItem_3->setPosition(Vec2((this->getContentSize().width / 2) + 50, 50));

	// create menu, it's an autorelease object
	auto menu = Menu::create(tMenuItem_1, tMenuItem_2, tMenuItem_3, NULL);
	menu->setPosition(Vec2::ZERO);
	mpBossLayer->addChild(menu, 10);


	mpBossSprite = Sprite::create("images/slime_boss.png");
	mpBossSprite->setAnchorPoint(Vec2(0.5, 0));
	mpBossSprite->setPosition(Vec2(400, 140));
	mpBossSprite->setFlipX(true);
	mpBossLayer->addChild(mpBossSprite, 1);
	mpBossSprite->runAction(tSlimeMotion->clone());


	mpLeftWinCountLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "0");
	mpLeftWinCountLabel->setPosition(Vec2(tCenter.x - 50, tCenter.y));
	mpLeftWinCountLabel->setScale(2);
	mpLeftWinCountLabel->setColor(Color3B(0, 100, 150));
	mpBossLayer->addChild(mpLeftWinCountLabel);

	mpRightWinCountLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "0");
	mpRightWinCountLabel->setPosition(Vec2(tCenter.x + 50, tCenter.y));
	mpRightWinCountLabel->setScale(2);
	mpRightWinCountLabel->setColor(Color3B(150, 100, 0));
	mpBossLayer->addChild(mpRightWinCountLabel);


	mpLeftCard = Sprite::create();
	mpLeftCard->setPosition(Vec2(100, 100));
	mpLeftCard->setScale(2, 2);
	mpLeftCard->setFlipX(true);
	mpBossLayer->addChild(mpLeftCard);

	mpRightCard = Sprite::create();
	mpRightCard->setPosition(Vec2(400, 100));
	mpRightCard->setScale(2, 2);
	mpBossLayer->addChild(mpRightCard);

	mpResultLabel = Label::createWithTTF("Result", "fonts/Marker Felt.ttf", 24);
	mpResultLabel->setPosition(Vec2((this->getContentSize().width / 2), 100));
	mpBossLayer->addChild(mpResultLabel, 2);

	mpBattleLayer->setVisible(true);

#pragma endregion

	return true;
}


//상속받은 부모의 enter,exit를 호출하지 않으면
//자식 enter,exit도 호출되지 않는다
//이벤트를 등록 후 해지 코드를 exit등의 메소드에서 호출하지 않으면
//x로 종료 시 에러가 발생한다
void SceneField::onEnter()
{
	Layer::onEnter();
	mpTouchEventOne = EventListenerTouchOneByOne::create();
	mpTouchEventOne->setSwallowTouches(true);
	mpTouchEventOne->onTouchBegan = CC_CALLBACK_2(SceneField::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpTouchEventOne, this);


}
void SceneField::onExit()
{
	//_eventDispatcher->removeEventListener(mpTouchEventOne);
	_eventDispatcher->removeEventListenersForTarget(this);
	Layer::onExit();
}



bool SceneField::onTouchBegan(Touch * tTouch, Event * unused_event)
{
	auto tTouchPos = tTouch->getLocation();
	Rect tBox = utils::getCascadeBoundingBox(mpDice);
	bool tIsTouch = tBox.containsPoint(tTouchPos);
	if (tIsTouch)
	{
		attackSlime();
	}
	return true;
}

void SceneField::attackSlime()
{
	int tNumber = mpDice->throwDice();

	if (tNumber >= 4)
	{
		mSlimeHp -= 5;
		mpSlimeHpSprite->setScale((float)mSlimeHp / mSlimeMaxHp, 1);
		if (mSlimeHp <= 0)
		{
			mpSlimeLayer->setVisible(false);
			mpBossLayer->setVisible(true);
		}
	}
	else
	{
		NextScene();
	}
}

void SceneField::doAction(Ref * pSender)
{
	auto tPressMenu = (MenuItem *)pSender;

	int tPlayer = tPressMenu->getTag();

	int tEnemy = rand() % 3 + 1;
	std::string tResultString;

	mpLeftCard->setTexture("images/sprite-" + std::to_string(tPlayer) + ".png");
	mpRightCard->setTexture("images/sprite-" + std::to_string(tEnemy) + ".png");

	int tResult = 0;

	switch (tPlayer)
	{
	case 1://가위,sprite-3-0.png
		switch (tEnemy)
		{
		case 1:
			tResult = 0;
			//tResultString = "Draw";
			break;
		case 2:
			tResult = -1;
			//tResultString = "Lose";
			break;
		case 3:
			tResult = 1;
			//tResultString = "Win";
			break;
		}
		break;
	case 2://바위,sprite-7-0.png
		switch (tEnemy)
		{
		case 1:
			tResult = 1;
			//tResultString = "Win";
			break;
		case 2:
			tResult = 0;
			//tResultString = "Draw";
			break;
		case 3:
			tResult = -1;
			//tResultString = "Lose";
			break;
		}
		break;
	case 3://보,sprite-0-0.png
		switch (tEnemy)
		{
		case 1:
			tResult = -1;
			break;
		case 2:
			tResult = 1;
			break;
		case 3:
			tResult = 0;
			break;
		}
		break;
	}

	switch (tResult)
	{
	case -1:
		mRightWinCount += 1;
		tResultString = "Lose";
		break;
	case 0:
		tResultString = "Draw";
		break;
	case 1:
		mLeftWinCount += 1;
		tResultString = "Win";
		break;
	}

	mpLeftWinCountLabel->setString(std::to_string(mLeftWinCount));
	mpRightWinCountLabel->setString(std::to_string(mRightWinCount));
	mpResultLabel->setString(tResultString);

	auto tEndAction = Sequence::create(
		FadeOut::create(0.7),
		CallFunc::create(CC_CALLBACK_0(SceneField::NextScene, this)),
		NULL
	);
	if (mLeftWinCount >= mWinCount)
	{
		mpBossSprite->runAction(tEndAction);
	}
	else if (mRightWinCount >= mWinCount)
	{
		mpPlayerAnimator->stopAni();
		mpPlayerAnimator->runAction(tEndAction);
	}
}

void SceneField::NextScene()
{
	Director::getInstance()->replaceScene(
		TransitionFade::create(1, SceneGameOver::createScene())
	);
}
