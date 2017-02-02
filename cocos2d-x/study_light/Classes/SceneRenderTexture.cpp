#include "SceneRenderTexture.h"

Scene * SceneRenderTexture::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneRenderTexture::create();
	scene->addChild(layer);
	return scene;
}

bool SceneRenderTexture::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto tWinSize = Director::getInstance()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tCenter = Vec2(visibleSize.width*0.5, visibleSize.height*0.5);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mpRenderNode = Node::create();
	this->addChild(mpRenderNode, 1);


	auto tBackSprite = Sprite::create("background.jpg");
	tBackSprite->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
	mpRenderNode->addChild(tBackSprite, 0);

	mpRenderTexture = RenderTexture::create(tWinSize.width, tWinSize.width, Texture2D::PixelFormat::RGBA8888);
	mpRenderTexture->retain();

	mpRenderSprite = Sprite::createWithTexture(mpRenderTexture->getSprite()->getTexture());
	mpRenderSprite->setAnchorPoint(Vec2(0, 0));
	mpRenderSprite->setPosition(visibleSize.width * 0.0, visibleSize.height * 0.0);
	mpRenderSprite->setScale(1);
	mpRenderSprite->setFlippedY(true);
	this->addChild(mpRenderSprite, 100);


	auto tGLProgram = GLProgram::createWithFilenames("shader/ccPositionTextureColor_noMVP_vert.vsh", "shader/default_shader.fsh");
	mpGLState = GLProgramState::getOrCreateWithGLProgram(tGLProgram);
	mpRenderSprite->setGLProgramState(mpGLState);

	mMousePos = tCenter;
	mCurrentLensSize = 0.05f;
	mpGLState->setUniformFloat("u_lensSize", mCurrentLensSize);
	mpGLState->setUniformVec3("u_lensColor", Vec3(0.9, 0.9, 0.9));
	mCurrentLensOutLine = 0.001;
	mpGLState->setUniformFloat("u_outLine", mCurrentLensOutLine);
	mCurrentLensInLine = 0.001;
	mpGLState->setUniformFloat("u_inLine", mCurrentLensInLine);
	mpGLState->setUniformVec2("u_resolution", mpRenderSprite->getContentSize());
	log("%f,%f", mpRenderSprite->getContentSize().width, mpRenderSprite->getContentSize().height);
	mpGLState->setUniformCallback("u_mouse", [this](GLProgram * tProg, Uniform * tUni)
	{
		tProg->setUniformLocationWith2f(
			tUni->location,
			this->mMousePos.x,
			this->mMousePos.y
		);
	});

	auto tLensTex = TextureCache::getInstance()->addImage("aim.png");
	mpGLState->setUniformTexture("u_lensTex", tLensTex);


	auto tHelloSprite = Sprite::create("HelloWorld.png");
	tHelloSprite->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5);
	mpRenderNode->addChild(tHelloSprite, 1);


	this->scheduleUpdate();
	return true;
}
void SceneRenderTexture::update(float dt)
{
	//mCurrentTime += dt * 0.01;
	//mpGLState->setUniformFloat("u_curTime", mCurrentTime);

	mpRenderTexture->begin();
	mpRenderNode->visit();
	mpRenderTexture->end();
}

void SceneRenderTexture::onEnter()
{
	LayerColor::onEnter();

	auto tMouseListener = EventListenerMouse::create();
	tMouseListener->onMouseMove = [this](EventMouse * tMouseEvent)
	{
		//this->mMousePos = tMouseEvent->getLocation();
	};
	tMouseListener->onMouseScroll = [this](EventMouse * tMouseEvent)
	{
		float val = tMouseEvent->getScrollY() * 0.01;
		val = -val;
		log("%f", val);
		this->mCurrentLensSize = clampf(this->mCurrentLensSize + val, 0, 5);
		log("%f", this->mCurrentLensSize);
		this->mpGLState->setUniformFloat("u_lensSize", this->mCurrentLensSize);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tMouseListener, this);

	
	auto tTouchListener = EventListenerTouchOneByOne::create();
	tTouchListener->onTouchBegan = CC_CALLBACK_2(SceneRenderTexture::onTouchBegan, this);
	tTouchListener->onTouchMoved = CC_CALLBACK_2(SceneRenderTexture::onTouchMoved, this);
	tTouchListener->onTouchEnded = CC_CALLBACK_2(SceneRenderTexture::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouchListener, this);


	auto tKeyboardListener = EventListenerKeyboard::create();
	tKeyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode tKeyCode, Event * tEvent)
	{
		switch (tKeyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			mCurrentTime += 0.01;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			mCurrentTime -= 0.01;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			break;
		}

		mpGLState->setUniformFloat("u_curTime", mCurrentTime);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyboardListener, this);

}

void SceneRenderTexture::onExit()
{

	mpRenderTexture->release();
	_eventDispatcher->removeEventListenersForTarget(this);
	LayerColor::onExit();
}


bool SceneRenderTexture::onTouchBegan(Touch * tTouch, Event * unused_event)
{
	return true;

}

void SceneRenderTexture::onTouchMoved(Touch * tTouch, Event * unused_event)
{
	mMousePos = tTouch->getLocation();
}

void SceneRenderTexture::onTouchEnded(Touch * tTouch, Event * unused_event)
{
}
