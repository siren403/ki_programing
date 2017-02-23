#include "SceneTitle.h"
#include "ScenePlay.h"
#include "StopWatch.h"

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

	auto background = Sprite::create("white4x4.jpg");
	background->setTextureRect(Rect(Vec2::ZERO, mVisibleSize));
	background->setPosition(mCenterPosition);
	mRenderNode->addChild(background);

	mMask = Sprite::create("enemy/whitemask.png");
	mMask->getTexture()->setAliasTexParameters();
	mMaskInitPosition = Vec2(mCenterPosition.x, mVisibleSize.height * 0.55);
	mMask->setPosition(mMaskInitPosition);
	mMask->setScale(0);
	mRenderNode->addChild(mMask, 0);



	mRenderTexture = RenderTexture::create(mVisibleSize.width, mVisibleSize.height,Texture2D::PixelFormat::RGBA8888);
	mRenderTexture->retain();
	
	mRenderSprite = Sprite::createWithTexture(mRenderTexture->getSprite()->getTexture());
	mRenderSprite->setPosition(mCenterPosition);
	mRenderSprite->setFlipY(true);
	this->addChild(mRenderSprite, 5);
	auto glProg = GLProgram::createWithFilenames("shader/ccPositionTextureColor_noMVP_vert.vsh", "shader/lens.fsh");
	mGLState = GLProgramState::getOrCreateWithGLProgram(glProg);
	mRenderSprite->setGLProgramState(mGLState);
	mRenderSprite->setVisible(true);
	

	mGLState->setUniformFloat("u_lensSize", UNIFORM_LENS_SIZE);
	mGLState->setUniformVec3("u_lensColor", Vec3(1.0, 1.0, 1.0));
	mGLState->setUniformFloat("u_outLine", UNIFORM_LENS_OUTLINE);
	mGLState->setUniformFloat("u_inLine", UNIFORM_LENS_OUTLINE);
	//mGLState->setUniformVec2("u_resolution", mRenderSprite->getContentSize());
	mGLState->setUniformVec2("u_resolution", Vec2(mRenderSprite->getContentSize().width, mRenderSprite->getContentSize().height*0.82));
	SetLensTargetPosition(mCenterPosition);
	mLensPosition = mLensTargetPosition;
	//mGLState->setUniformVec2("u_mouse", mLensPosition);
	mGLState->setUniformCallback("u_mouse", [this](GLProgram * tProg, Uniform * tUni)
	{
		tProg->setUniformLocationWith2f(
			tUni->location,
			this->mLensPosition.x,
			this->mLensPosition.y
		);
	});

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

	/*
	mUpdateFunctions.push_back([this](float dt)
	{
		return false;
	});
	*/
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 2)
		{
			mUpdateFunctionWatch->OnReset();
			mExclamationMark->runAction(EaseExponentialOut::create(ScaleTo::create(0.3, 1)));
				
			return true;
		}
		return false;
	});//show exclamation mark
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 0.3)
		{
			mUpdateFunctionWatch->OnReset();
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
		if (mIsTouchBegan)
		{
			mExclamationMark->runAction(EaseExponentialOut::create(ScaleTo::create(0.3, 0)));
			return true;
		}
		return false;
	});//touch wait
	mUpdateFunctions.push_back([this](float dt) 
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mUpdateFunctionWatch->GetAccTime() >= 0.5)
		{
			mUpdateFunctionWatch->OnReset();
			mMask->runAction(EaseExponentialOut::create(ScaleTo::create(0.85, 4)));
			return true;
		}
		return false;
	});//show mask

	mTitleScriptLabel = Label::create("script", "fonts/NanumGothicBold.ttf", 28);
	mTitleScriptLabel->setPosition(mVisibleSize.width*0.5, mVisibleSize.height * 0.4);
	mTitleScriptLabel->setColor(Color3B::BLACK);
	mTitleScriptLabel->setAnchorPoint(Vec2(0.5, 1));
	mRenderNode->addChild(mTitleScriptLabel);

	mTitleScript.push_back("첫번째 대사 \n 1-1 script \n 1-1 script");
	mTitleScript.push_back("두번째 대사");
	mTitleScript.push_back("세번째 대사");
	mTitleScript.push_back("네번째 대사");
	mTitleScript.push_back("다섯번째 대사");
	mUpdateFunctions.push_back([this](float dt)
	{
		mUpdateFunctionWatch->OnUpdate(dt);
		if (mTitleScript.size() > 0 && mTitleScriptIndex < mTitleScript.size())
		{
			if (mUpdateFunctionWatch->GetAccTime() >= 0.05)
			{
				if (mScriptCharIndex < mTitleScript[mTitleScriptIndex].length())
				{
					mTitleScriptLabel->setString(mTitleScript[mTitleScriptIndex].substr(0, mScriptCharIndex + 1));
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
		Director::getInstance()->replaceScene(TransitionFade::create(1,ScenePlay::createScene()));
		return true;
	});//next scene
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

	//setAccelerometerEnabled(true);

}
void SceneTitle::onExit()
{
	//setAccelerometerEnabled(false);

	CC_SAFE_RELEASE_NULL(mRenderTexture);
	_eventDispatcher->removeEventListenersForTarget(this);
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
	//SetLensTargetPosition(pos);
	if (mStopWatch->GetAccTime() >= 5)
	{
		mStopWatch->OnReset();
	}

	mLensPosition = ccpLerp(mLensPosition, mLensTargetPosition, dt);
	mLensPosition = ccpClamp(mLensPosition, Vec2::ZERO, mVisibleSize);

	//mRenderTexture->beginWithClear(1,1,1,1);
	mRenderTexture->begin();
	mRenderNode->visit();
	mRenderTexture->end();

	mIsTouchBegan = false;
}
bool SceneTitle::onTouchBegan(Touch * touch, Event * unused_event)
{
	//SetLensTargetPosition(touch->getLocation());
	mIsTouchBegan = true;
	return true;
}

void SceneTitle::onTouchMoved(Touch * touch, Event * unused_event)
{
	//SetLensTargetPosition(touch->getLocation());
}

void SceneTitle::onTouchEnded(Touch * touch, Event * unused_event)
{
	//mLensTargetPosition = mMask->getPosition();
	//SetLensTargetPosition(mCenterPosition);
	//Director::getInstance()->replaceScene(TransitionFade::create(1,ScenePlay::createScene()));
}

void SceneTitle::onAcceleration(Acceleration * acc, Event * unused_event)
{
}

void SceneTitle::SetLensTargetPosition(Vec2 pos)
{
	mLensTargetPosition = Vec2(mVisibleSize.width - pos.x, mVisibleSize.height - pos.y);
}
