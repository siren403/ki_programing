#include "ShaderTest.h"

bool ShaderTest::init()
{
	if (!Node::init())
	{
		return false;
	}
	

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto tCenter = Vec2(visibleSize.width*0.5, visibleSize.height*0.5);

	mSprite = Sprite::create("HelloWorld_2.png");
	//float tScale = Director::getInstance()->getContentScaleFactor();
	//mSprite->setScale(tScale);
	mSprite->setPosition(tCenter);
	mSprite->setScaleX(2.67f);
	mSprite->setScaleY(2.67f);
	this->addChild(mSprite, 1);

	std::string str = "11";

	auto tGLProgram = GLProgram::createWithFilenames("shader/ccPositionTextureColor_noMVP_vert.vsh", "shader/default_shader.fsh");
	mGLState = GLProgramState::getOrCreateWithGLProgram(tGLProgram);
	mSprite->setGLProgramState(mGLState);

	mCurrentLensSize = 0.2f;
	mGLState->setUniformFloat("u_lensSize", mCurrentLensSize);
	mGLState->setUniformVec3("u_lensColor", Vec3(0.9,0.9,0.9));
	mCurrentLensOutLine = 0.01;
	mGLState->setUniformFloat("u_outLine", mCurrentLensOutLine);
	mCurrentLensInLine = 0.01;
	mGLState->setUniformFloat("u_inLine", mCurrentLensInLine);
	mGLState->setUniformVec2("u_resolution", visibleSize);
	mGLState->setUniformCallback("u_mouse", [this](GLProgram * tProg,Uniform * tUni)
	{
		tProg->setUniformLocationWith2f(
			tUni->location, 
			this->mMousePos.x, 
			this->mMousePos.y
		);
	});

	auto tLensTex = TextureCache::getInstance()->addImage("aim.png");
	mGLState->setUniformTexture("u_lensTex", tLensTex);

	mAimSprite = Sprite::create("aim.png");
	mAimSprite->setScale(0.4);
	mAimSprite->setColor(Color3B::GREEN);
	this->addChild(mAimSprite, 10);

	/*
	uniform vec2 u_resolution;
	uniform vec2 u_mouse;
	*/
	auto tMouseListener = EventListenerMouse::create();
	tMouseListener->onMouseMove = [this](EventMouse * tMouseEvent) 
	{
		//this->mMousePos = tMouseEvent->getLocation();
	};
	tMouseListener->onMouseScroll = [this](EventMouse * tMouseEvent)
	{
		float val = tMouseEvent->getScrollY() * 0.1;
		val = -val;
		log("%f", val);
		this->mCurrentLensSize = clampf(this->mCurrentLensSize + val, 0, 5);
		log("%f", this->mCurrentLensSize);
		this->mGLState->setUniformFloat("u_lensSize", this->mCurrentLensSize);
	};
	tMouseListener->onMouseDown = [this](EventMouse * tMouseEvent)
	{
		bool isOutLine = false;

		if (isOutLine)
		{
			if (tMouseEvent->getMouseButton() == MOUSE_BUTTON_LEFT)
			{
				this->mCurrentLensOutLine += 0.01;
			}
			else if (tMouseEvent->getMouseButton() == MOUSE_BUTTON_RIGHT)
			{
				this->mCurrentLensOutLine -= 0.01;
			}
			this->mCurrentLensOutLine = clampf(this->mCurrentLensOutLine, 0, 1);
			//this->mGLState->setUniformFloat("u_outLine", mCurrentLensOutLine);
		}
		else
		{
			if (tMouseEvent->getMouseButton() == MOUSE_BUTTON_LEFT)
			{
				mCurrentLensInLine += 0.01;
			}
			else if (tMouseEvent->getMouseButton() == MOUSE_BUTTON_RIGHT)
			{
				mCurrentLensInLine -= 0.01;
			}
			mCurrentLensInLine = clampf(mCurrentLensInLine, 0, 1);
			//mGLState->setUniformFloat("u_inLine", mCurrentLensInLine);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tMouseListener, this);

	/*auto tKeyboardListener = EventListenerKeyboard::create();
	tKeyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode tKeyCode,Event * tEvent) 
	{
		switch (tKeyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			this->mSprite->getGLProgramState()->setUniformVec4("u_color", Vec4(1.0, 0.0, 0.0, 1.0));
			break;
		case EventKeyboard::KeyCode::KEY_S:
			this->mSprite->getGLProgramState()->setUniformVec4("u_color", Vec4(0.0, 1.0, 0.0, 1.0));
			break;
		case EventKeyboard::KeyCode::KEY_D:
			this->mSprite->getGLProgramState()->setUniformVec4("u_color", Vec4(0.0, 0.0, 1.0, 1.0));
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyboardListener, this);*/

	auto tTouchListener = EventListenerTouchOneByOne::create();
	tTouchListener->onTouchBegan = CC_CALLBACK_2(ShaderTest::OnTouchBegan, this);
	tTouchListener->onTouchMoved = CC_CALLBACK_2(ShaderTest::OnTouchMoved, this);
	tTouchListener->onTouchEnded = CC_CALLBACK_2(ShaderTest::OnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouchListener, this);
	//this->scheduleUpdate();
	return true;
}

void ShaderTest::update(float dt)
{
	log("update loop");
}

void ShaderTest::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	Node::onExit();
}

Vec2 ShaderTest::GetUV(Vec2 tTexCoord, Vec2 tResolution, Vec2 tMousePos)
{
	Vec2 p = Vec2(tTexCoord.x / tResolution.x, tTexCoord.y / tResolution.x);

	float prop = tResolution.x / tResolution.y;

	Vec2 m = Vec2(0.5, 0.5 / prop);

	Vec2 d = p - m;

	float r = sqrt(ccpDot(d, d));

	float power = (2.0*3.141592 / (2.0*sqrt(ccpDot(m, m)))) *
		(tMousePos.x / tResolution.x - 0.5);

	log("power %f", power);

	float bind;

	if (power > 0.0)
	{
		bind = sqrt(ccpDot(m, m));
	}
	else
	{
		if (prop < 1.0)
		{
			bind = m.x;
		}
		else
		{
			bind = m.y;
		}
	}
	log("bind %f", bind);


	Vec2 uv;
	if (power > 0.0)
	{
		uv = m + ccpNormalize(d) * tan(r*power)*bind / tan(bind * power);
	}
	else if (power < 0.0)
	{
		uv = m + ccpNormalize(d) * atan(r*-power*10.0)*bind / atan(-power * bind * 10.0);
	}
	else
	{
		uv = p;
	}
	return Vec2(uv.x, -uv.y * prop);
}

bool ShaderTest::OnTouchBegan(Touch * tTouch, Event * unused_event)
{
	return true;
}

void ShaderTest::OnTouchMoved(Touch * tTouch, Event * unused_event)
{
	mMousePos = tTouch->getLocationInView();
	mAimSprite->setPosition(tTouch->getLocation());
	log("%f,%f", tTouch->getLocation().x, tTouch->getLocation().y);

}

void ShaderTest::OnTouchEnded(Touch * tTouch, Event * unused_event)
{

}
