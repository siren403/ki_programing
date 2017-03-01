#include "SceneTitle.h"
#include "ScenePlay.h"
#include "StopWatch.h"
#include "DataManager.h"
#include "GameSharing.h"

#pragma execution_character_set("utf-8")

#define UNIFORM_LENS_OUTLINE 0.001
#define UNIFORM_LENS_SIZE 1.5f

Scene * SceneTitle::createScene()
{
	auto scene = Scene::create();
	auto title = SceneTitle::create();
	scene->addChild(title);
	return scene;
}

bool SceneTitle::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}


	mVisibleSize = Director::getInstance()->getVisibleSize();
	mCenterPosition = Vec2(mVisibleSize.width / 2, mVisibleSize.height/2);

	//--------------------

	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);

	/*auto background = Sprite::create("white4x4.jpg");
	background->setTextureRect(Rect(Vec2::ZERO, mVisibleSize));
	background->setPosition(mCenterPosition);
	mRenderNode->addChild(background);*/

	mMask = Sprite::create("enemy/whitemask.png");
	mMask->getTexture()->setAliasTexParameters();
	mMaskInitPosition = Vec2(mCenterPosition.x, mVisibleSize.height * 0.55);
	mMask->setPosition(mMaskInitPosition);
	mMask->setScale(0);
	mRenderNode->addChild(mMask, 0);

	auto screenBezel = Sprite::create("screen_bezel.png");
	screenBezel->getTexture()->setAliasTexParameters();
	screenBezel->setScale(CC_CONTENT_SCALE_FACTOR() * 2);
	screenBezel->setPosition(mCenterPosition);
	mRenderNode->addChild(screenBezel, 10);

	mTitleNameLabel = Label::create("ONE\nLIFE", "fonts/NotoSansKR-Regular-Hestia.otf", 120);
	for (int i = 0; i < mTitleNameLabel->getStringLength(); i++)
	{
		auto letter = mTitleNameLabel->getLetter(i);
		if (letter != nullptr)
		{
			letter->setColor(i % 2 == 0 ? Color3B::WHITE : Color3B::BLACK);
		}
	}
	mTitleNameLabel->setPosition(mCenterPosition.x, mVisibleSize.height*0.7);
	mRenderNode->addChild(mTitleNameLabel, screenBezel->getLocalZOrder() + 1);


	mTitleScriptLabel = Label::create("", "fonts/NotoSansKR-Regular-Hestia.otf", 45);
	mTitleScriptLabel->setPosition(mVisibleSize.width * 0.5, mVisibleSize.height * 0.35);
	mTitleScriptLabel->setColor(Color3B::BLACK);
	mTitleScriptLabel->setAnchorPoint(Vec2(0.5, 1));
	mRenderNode->addChild(mTitleScriptLabel);


	mTitleScript = DataManager::GetInstance()->GetTitleScripts();

#pragma region Watchs

	mStopWatch = StopWatch::create();
	mStopWatch->SetAutoUpdate(true);
	mStopWatch->OnStart();
	this->addChild(mStopWatch);
	
	mUpdateFunctionWatch = StopWatch::create();
	mUpdateFunctionWatch->OnStart();
	this->addChild(mUpdateFunctionWatch);

#pragma endregion

#pragma region UpdateFunctions
	mExclamationMark = Sprite::create("ui/exclamation_mark.png");
	mExclamationMark->setPosition(mVisibleSize.width * 0.5, mVisibleSize.height * 0.55);
	mExclamationMark->setScale(0);
	mRenderNode->addChild(mExclamationMark, mMask->getLocalZOrder() + 1);

	mTitleScriptLabel->setString(mTitleScript->at(mTitleScriptIndex++));
	mUpdateFunctions.push_back([this](float dt)
	{
		if (mIsTouchBegan)
		{
			mTitleScriptLabel->setString("\n");
			mTitleNameLabel->runAction(FadeOut::create(0.3f));
			return true;
		}
		return false;
	});//show exclamation mark
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 0.5)
		{
			mUpdateFunctionWatch->OnReset();
			mExclamationMark->runAction(EaseExponentialOut::create(ScaleTo::create(0.3, 1)));
			mExclamationMark->runAction(RepeatForever::create(
				Sequence::create(
					EaseSineInOut::create(MoveBy::create(1, Vec2(0, -15))),
					EaseSineInOut::create(MoveBy::create(1, Vec2(0, 15))),
					nullptr
				)
			));
			return true;
		}
		return false;
	});
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 1)
		{
			mExclamationMark->runAction(EaseExponentialOut::create(ScaleTo::create(0.3, 0)));
			mUpdateFunctionWatch->OnReset();
			return true;
		}
		return false;
	});
	mUpdateFunctions.push_back([this](float dt) 
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 0.5)
		{
			mUpdateFunctionWatch->OnReset();
			mMask->runAction(EaseExponentialOut::create(ScaleTo::create(0.85, 6)));
			return true;
		}
		return false;
	});//show mask
	
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mTitleScript->size() > 0 && mTitleScriptIndex < mTitleScript->size())
		{
			if (mUpdateFunctionWatch->GetAccTime() >= 0.05)
			{
				if (mScriptCharIndex < mTitleScript->at(mTitleScriptIndex).length())
				{
					mTitleScriptLabel->setString(mTitleScript->at(mTitleScriptIndex).substr(0, mScriptCharIndex + 1));
					mUpdateFunctionWatch->OnReset();
					mScriptCharIndex++;
				}
				else
				{
					if (mIsTouchBegan)
					{
						mTitleScriptLabel->setString("\n");
						mScriptCharIndex = 0;
						mTitleScriptIndex++;
					}
				}
			}
			return false;
		}
		return true;
	});//play script
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 1)
		{
			mMask->runAction(EaseExponentialOut::create(ScaleTo::create(0.3, 0)));
			Director::getInstance()->replaceScene(TransitionFade::create(1, ScenePlay::createScene()));
			return true;
		}
		return false;
	});
#pragma endregion

#pragma region GooglePlay

	//auto btn = MenuItemLabel::create()
	auto btnBoard = MenuItemFont::create("leaderboard", [](Ref * sender) 
	{
		GameSharing::ShowLeaderboards(0);
	});
	btnBoard->setColor(Color3B::RED);
	btnBoard->setPosition(mCenterPosition.x, mVisibleSize.height*0.9f);

	auto btnArchievements = MenuItemFont::create("archievements", [](Ref * sender)
	{
		GameSharing::ShowAchievementsUI();
	});
	btnArchievements->setPosition(mCenterPosition.x, mVisibleSize.height*0.8f);
	btnArchievements->setColor(Color3B::RED);

	auto btnsubmit = MenuItemFont::create("submit", [](Ref * sender)
	{
		GameSharing::SubmitScore(777, 0);
		GameSharing::UnlockAchivement(0);
	});
	btnsubmit->setPosition(mCenterPosition.x, mVisibleSize.height*0.7f);
	btnsubmit->setColor(Color3B::RED);

	auto google = Menu::create(btnBoard, btnArchievements, btnsubmit, nullptr);
	google->setPosition(Vec2::ZERO);
	mRenderNode->addChild(google);

#pragma endregion


	this->scheduleUpdate();
	return true;
}

void SceneTitle::onEnter()
{
	LayerColor::onEnter();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SceneTitle::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SceneTitle::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SceneTitle::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SceneTitle::onKeyPressed, this);

}
void SceneTitle::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);
	mUpdateFunctions.clear();
	this->unscheduleUpdate();
	LayerColor::onExit();
}


void SceneTitle::update(float dt)
{
	if (mUpdateFunctions.size() > 0 && mUpdateFunctionIndex < mUpdateFunctions.size())
	{
		if (mUpdateFunctions[mUpdateFunctionIndex](dt))
		{
			mUpdateFunctionIndex++;
		}
	}

	Vec2 pos = mMaskInitPosition;
	pos.x += sin((3.14159 * 2) * (mStopWatch->GetAccTime() / 5)) * 13;
	pos.y += cos((3.14159 * 2) * (mStopWatch->GetAccTime() / 5)) * 16;
	mMask->setPosition(pos);
	if (mStopWatch->GetAccTime() >= 5)
	{
		mStopWatch->OnReset();
	}

	mIsTouchBegan = false;
}
bool SceneTitle::onTouchBegan(Touch * touch, Event * unused_event)
{
	mIsTouchBegan = true;
	return true;
}

void SceneTitle::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void SceneTitle::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void SceneTitle::onKeyPressed(EventKeyboard::KeyCode key, Event * event)
{
	if (key == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		GameSharing::ExitGame();
		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
		#endif
	}
}




