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

	mMask = Sprite::create("enemy/whitemask.png");
	mMask->getTexture()->setAliasTexParameters();
	mMask->setPosition(mCenterPosition.x,mVisibleSize.height * 0.5);
	mMask->setScale(4);
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
	mGLState->setUniformVec2("u_resolution", mRenderSprite->getContentSize());
	mLensTargetPosition = mCenterPosition;
	mLensPosition = mCenterPosition;
	//mGLState->setUniformVec2("u_mouse", mLensPosition);
	mGLState->setUniformCallback("u_mouse", [this](GLProgram * tProg, Uniform * tUni)
	{
		tProg->setUniformLocationWith2f(
			tUni->location,
			this->mLensPosition.x,
			this->mLensPosition.y
		);
	});

	mStopWatch = StopWatch::create();
	mStopWatch->SetAutoUpdate(true);
	mStopWatch->OnStart();
	this->addChild(mStopWatch);

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
	//mRenderTexture->beginWithClear(1,1,1,1);
	mRenderTexture->begin();
	mRenderNode->visit();
	mRenderTexture->end();


	/*Vec2 pos = mCenterPosition;
	float min = pos.y * 0.9;
	float max = pos.y * 0.2;
	log("%f", sin(mStopWatch->GetAccTime()));
	pos.y = min + (sin(mStopWatch->GetAccTime()) * max);
	SetLensTargetPosition(pos);
	if (mStopWatch->GetAccTime() >= 3.14159)
	{
		mStopWatch->OnReset();
	}*/


	mLensPosition = ccpLerp(mLensPosition, mLensTargetPosition, dt);
	mLensPosition = ccpClamp(mLensPosition, Vec2::ZERO, mVisibleSize);


}
bool SceneTitle::onTouchBegan(Touch * touch, Event * unused_event)
{
	SetLensTargetPosition(touch->getLocation());
	return true;
}

void SceneTitle::onTouchMoved(Touch * touch, Event * unused_event)
{
	SetLensTargetPosition(touch->getLocation());
}

void SceneTitle::onTouchEnded(Touch * touch, Event * unused_event)
{
	//mLensTargetPosition = mMask->getPosition();
	SetLensTargetPosition(mCenterPosition);
}

void SceneTitle::onAcceleration(Acceleration * acc, Event * unused_event)
{
}

void SceneTitle::SetLensTargetPosition(Vec2 pos)
{
	mLensTargetPosition = Vec2(mVisibleSize.width - pos.x, mVisibleSize.height - pos.y);
}
