#include "CardGame.h"
#include "SimpleAudioEngine.h"
#include <time.h>
#include <stdlib.h>
USING_NS_CC;

cocos2d::Scene * CCardGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CCardGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CCardGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	srand(time(NULL));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 tCenter = Vec2(visibleSize.width / 2, visibleSize.height/2);

#pragma region InitTitleLayer
	mTitleLayer = Layer::create();
	mTitleLayer->retain();	
	this->addChild(mTitleLayer,1);

	mTitleLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "Slime");
	mTitleLabel->retain();
	mTitleLabel->setPosition(tCenter);
	mTitleLabel->setAnchorPoint(Vec2(0.6,0.5));
	mTitleLabel->setScale(2);
	mTitleLayer->addChild(mTitleLabel);

#pragma endregion

#pragma region InitiBattleLayer

	mBattleLayer = Layer::create();
	mBattleLayer->retain();
	mBattleLayer->setVisible(false);
	this->addChild(mBattleLayer);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CCardGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto tBattleMenu = Menu::create(closeItem, NULL);
	tBattleMenu->setPosition(Vec2::ZERO);
	mBattleLayer->addChild(tBattleMenu);
	
	mPlayerSprite = Sprite::create("images/grossini.png");
	mPlayerSprite->retain();
	mPlayerSprite->setAnchorPoint(Vec2(0.5, 0));
	mPlayerSprite->setPosition(Vec2(100, 160));
	mBattleLayer->addChild(mPlayerSprite, 1);


	//==========================================
	mSlimeLayer = Layer::create();
	mSlimeLayer->retain();
	mBattleLayer->addChild(mSlimeLayer);

	auto tAttackSlimeMenuItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CCardGame::attackSlime, this));
	tAttackSlimeMenuItem->setPosition(tCenter);

	auto tSlimeMenu = Menu::create(
		tAttackSlimeMenuItem,
		NULL
	);
	tSlimeMenu->setPosition(Vec2::ZERO);
	tSlimeMenu->setScale(2);
	mSlimeLayer->addChild(tSlimeMenu, 10);


	mSlimeSprite = Sprite::create("images/slime.png");
	mSlimeSprite->retain();
	mSlimeSprite->setAnchorPoint(Vec2(0.5, 0));
	mSlimeSprite->setPosition(Vec2(400, 160));
	mSlimeSprite->setFlipX(true);
	mSlimeLayer->addChild(mSlimeSprite, 1);
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
	mSlimeSprite->runAction(tSlimeMotion->clone());


	mSlimeHpSprite = Sprite::create("images/white-512x512.png");
	mSlimeHpSprite->retain();
	mSlimeHpSprite->setColor(Color3B::RED);
	mSlimeHpSprite->setTextureRect(Rect(0, 0, 80, 5));
	mSlimeHpSprite->setAnchorPoint(Vec2(0.5, 0));
	mSlimeHpSprite->setPosition(Vec2(mSlimeSprite->getPosition().x, mSlimeSprite->getPosition().y + 100));
	mSlimeLayer->addChild(mSlimeHpSprite);

	//=========================================


	mBossLayer = Layer::create();
	mBossLayer->retain();
	mBossLayer->setVisible(false);
	mBattleLayer->addChild(mBossLayer);

	auto tMenuItem_1 = MenuItemImage::create(
		"images/sprite-1.png", 
		"images/sprite-1.png",
		CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_1->setTag(1);
	tMenuItem_1->setPosition(Vec2((this->getContentSize().width / 2) - 50, 50));

	auto tMenuItem_2 = MenuItemImage::create(
		"images/sprite-2.png",
		"images/sprite-2.png",
		CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_2->setTag(2);
	tMenuItem_2->setPosition(Vec2((this->getContentSize().width / 2), 50));

	auto tMenuItem_3 = MenuItemImage::create(
		"images/sprite-3.png",
		"images/sprite-3.png",
		CC_CALLBACK_1(CCardGame::DoAction, this));
	tMenuItem_3->setTag(3);
	tMenuItem_3->setPosition(Vec2((this->getContentSize().width / 2) + 50, 50));

	// create menu, it's an autorelease object
	auto menu = Menu::create(tMenuItem_1, tMenuItem_2, tMenuItem_3, NULL);
	menu->setPosition(Vec2::ZERO);
	mBossLayer->addChild(menu, 10);


	mBossSprite = Sprite::create("images/slime_boss.png");
	mBossSprite->retain();
	mBossSprite->setAnchorPoint(Vec2(0.5, 0));
	mBossSprite->setPosition(Vec2(400, 140));
	mBossSprite->setFlipX(true);
	mBossLayer->addChild(mBossSprite, 1);
	mBossSprite->runAction(tSlimeMotion->clone());


	mLeftWinCountLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "0");
	mLeftWinCountLabel->retain();
	mLeftWinCountLabel->setPosition(Vec2(tCenter.x - 50, tCenter.y));
	mLeftWinCountLabel->setScale(2);
	mLeftWinCountLabel->setColor(Color3B(0, 100, 150));
	mBossLayer->addChild(mLeftWinCountLabel);

	mRightWinCountLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "0");
	mRightWinCountLabel->retain();
	mRightWinCountLabel->setPosition(Vec2(tCenter.x + 50, tCenter.y));
	mRightWinCountLabel->setScale(2);
	mRightWinCountLabel->setColor(Color3B(150, 100, 0));
	mBossLayer->addChild(mRightWinCountLabel);


	mLeftCard = Sprite::create("images/sprite-1.png");
	mLeftCard->retain();
	mLeftCard->setPosition(Vec2(100, 100));
	mLeftCard->setScale(2, 2);
	mBossLayer->addChild(mLeftCard);

	mRightCard = Sprite::create("images/sprite-1.png");
	mRightCard->retain();
	mRightCard->setPosition(Vec2(400, 100));
	mRightCard->setScale(2, 2);
	mBossLayer->addChild(mRightCard);

	mResultLabel = Label::createWithTTF("Result", "fonts/Marker Felt.ttf", 24);
	mResultLabel->retain();
	mResultLabel->setPosition(Vec2((this->getContentSize().width / 2), 100));
	mBossLayer->addChild(mResultLabel,2);

#pragma endregion


	mTitleLabel->setPosition(Vec2(-100, tCenter.y));
	auto tTitleSeq = Sequence::create
	(
		EaseExponentialOut::create(MoveTo::create(1.5, tCenter)),
		DelayTime::create(1),
		FadeOut::create(1),
		CallFunc::create(CC_CALLBACK_0(CCardGame::startGame, this)),
		NULL
	);

	mTitleLabel->runAction(tTitleSeq);

	return true;
}

void CCardGame::menuCloseCallback(cocos2d::Ref * pSender)
{

	mTitleLayer->removeAllChildren();
	if (NULL != mTitleLabel)
	{
		mTitleLabel->release();
		mTitleLabel = NULL;
	}

	this->removeChild(mTitleLayer);
	if (NULL != mTitleLayer)
	{
		mTitleLayer->release();
		mTitleLayer = NULL;
	}



	//=============================
	mBattleLayer->removeAllChildren();


	mSlimeLayer->removeAllChildren();
	if (NULL != mSlimeHpSprite)
	{
		mSlimeHpSprite->release();
		mSlimeHpSprite = NULL;
	}
	if (NULL != mSlimeSprite)
	{
		mSlimeSprite->release();
		mSlimeSprite = NULL;
	}

	if (NULL != mSlimeLayer)
	{
		mSlimeLayer->release();
		mSlimeLayer = NULL;
	}
	//=============================
	
	mBossLayer->removeAllChildren();
	if (NULL != mBossSprite)
	{
		mBossSprite->release();
		mBossSprite = NULL;
	}
	if (NULL != mLeftWinCountLabel)
	{
		mLeftWinCountLabel->release();
		mLeftWinCountLabel = NULL;
	}
	if (NULL != mRightWinCountLabel)
	{
		mRightWinCountLabel->release();
		mRightWinCountLabel = NULL;
	}
	if (NULL != mLeftCard)
	{
		mLeftCard->release();
		mLeftCard = NULL;
	}
	if (NULL != mRightCard)
	{
		mRightCard->release();
		mRightCard = NULL;
	}
	if (NULL != mResultLabel)
	{
		mResultLabel->release();
		mResultLabel = NULL;
	}
	if (NULL != mBossLayer)
	{
		mBossLayer->release();
		mBossLayer = NULL;
	}
	//=============================
	if (NULL != mPlayerSprite)
	{
		mPlayerSprite->release();
		mPlayerSprite = NULL;
	}
	this->removeChild(mBattleLayer);
	if (NULL != mBattleLayer)
	{
		mBattleLayer->release();
		mBattleLayer = NULL;
	}


	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CCardGame::DoAction(Ref * pSender)
{
	auto tPressMenu = (MenuItem *)pSender;

	int tPlayer = tPressMenu->getTag();

	int tEnemy = rand() % 3 + 1;
	std::string tResultString;

	mLeftCard->setTexture("images/sprite-" + std::to_string(tPlayer) + ".png");
	mRightCard->setTexture("images/sprite-" + std::to_string(tEnemy) + ".png");

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

	mLeftWinCountLabel->setString(std::to_string(mLeftWinCount));
	mRightWinCountLabel->setString(std::to_string(mRightWinCount));
	mResultLabel->setString(tResultString);


	if (mLeftWinCount >= mWinCount)
	{
		mBossSprite->runAction(
			Sequence::create(
				FadeOut::create(0.7),
				CallFunc::create(CC_CALLBACK_0(CCardGame::endGame, this)),
				NULL
			)
		);
	}
	else if (mRightWinCount >= mWinCount)
	{
		mPlayerSprite->runAction(
			Sequence::create(
				FadeOut::create(0.6),
				CallFunc::create(CC_CALLBACK_0(CCardGame::endGame, this)),
				NULL
			)
		);
	}
}

void CCardGame::startGame()
{
	mTitleLayer->setVisible(false);
	mBattleLayer->setVisible(true);
}

void CCardGame::attackSlime(Ref * pSender)
{
	mSlimeHp -= 1;
	mSlimeHpSprite->setScale((float)mSlimeHp / mSlimeMaxHp, 1);
	if (mSlimeHp <= 0)
	{
		mSlimeLayer->setVisible(false);
		mBossLayer->setVisible(true);
	}

}

void CCardGame::endGame()
{
	//mBossLayer->setVisible(false);
}
