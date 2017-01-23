#include "SceneBox2D.h"

Scene * SceneBox2D::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneBox2D::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SceneBox2D::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mWinSize = Director::getInstance()->getWinSize();

	b2Vec2 tGravity = b2Vec2(0.0f, -30.0f);

	mpb2World = new b2World(tGravity);
	mpb2World->SetAllowSleeping(true);
	mpb2World->SetContinuousPhysics(true);
	
	bool isDebug = true;
	if (isDebug)
	{
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		mpb2World->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		m_debugDraw->SetFlags(flags);
	}


	b2BodyDef tGroundBodyDef;
	tGroundBodyDef.position.Set(0, 0);

	b2Body * tpGroundBody = mpb2World->CreateBody(&tGroundBodyDef);

	b2EdgeShape tGroundEdge;
	b2FixtureDef tBoxShapeDef;
	tBoxShapeDef.shape = &tGroundEdge;

	tGroundEdge.Set(b2Vec2(0, 0), b2Vec2(mWinSize.width / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	tGroundEdge.Set(b2Vec2(0, 0), b2Vec2(0,mWinSize.height / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//top
	tGroundEdge.Set(
		b2Vec2(0, mWinSize.height / PTM_RATIO),
		b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//right
	tGroundEdge.Set(b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO),
		b2Vec2(mWinSize.width / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);


	this->schedule(CC_SCHEDULE_SELECTOR(SceneBox2D::updateTick));

	mpListener = EventListenerTouchOneByOne::create();

	//임의의 객체가 터치 이벤트를 받으면 터치 이벤트가 사라짐.
	mpListener->setSwallowTouches(true);

	mpListener->onTouchBegan = CC_CALLBACK_2(SceneBox2D::onTouchBegan, this);
	mpListener->onTouchMoved = CC_CALLBACK_2(SceneBox2D::onTouchMoved, this);
	mpListener->onTouchEnded = CC_CALLBACK_2(SceneBox2D::onTouchEnded, this);

	//이벤트리스너를 추가한다.
	//씬 그래프 상의 우선순위에 따라 터치 이벤트를 받는다.
	//( 이를테면, 위에 있는 스프라이트가 먼저 터치 이벤트를 받는다. )
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mpListener, this);


	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBox2D::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));



	auto tBtnGoMove = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SceneBox2D::onClickBtnGoMove, this));

	tBtnGoMove->setPosition(Vec2(origin.x + visibleSize.width - tBtnGoMove->getContentSize().width / 2, 100.0f));



	auto tTextField = TextFieldTTF::create();

	tTextField->setWidth(150);
	tTextField->setHeight(100);
	tTextField->setString("text field");
	tTextField->setColor(Color3B::GRAY);
	//tTextField->setBMFontSize(24);

	tTextField->setPosition(Vec2(400, 240));



	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, tBtnGoMove, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	mpLayer_0 = Layer::create();
	mpLayer_0->retain();
	this->addChild(mpLayer_0);


	mpLayer_1 = Layer::create();
	mpLayer_1->retain();

	this->addChild(mpLayer_1, 10);




	mplblDebug = Label::createWithTTF("DEBUG: ", "fonts/BMJUA_ttf.ttf", 18);
	mplblDebug->setOpacity(128);
	mplblDebug->setAnchorPoint(Vec2(0, 0));
	mplblDebug->setPosition(Vec2(50, 50));

	mpLayer_1->addChild(mplblDebug, 100);






	this->scheduleUpdate();

	return true;
}

void SceneBox2D::update(float dt)
{
	
}

void SceneBox2D::updateTick(float dt)
{
	if (NULL == mpb2World)
	{
		return;
	}


	int tVelocityIterations = 8;
	int tPositionIterations = 3;

	mpb2World->Step(dt, tVelocityIterations, tPositionIterations);




	for (b2Body *tpBody = mpb2World->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (NULL != tpBody->GetUserData())
		{
			Sprite *tpSprite = (Sprite *)tpBody->GetUserData();

			tpSprite->setPosition(Vec2(tpBody->GetPosition().x*PTM_RATIO,
				tpBody->GetPosition().y*PTM_RATIO));

			tpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES((tpBody->GetAngle())));
		}
	}
}

int SceneBox2D::doRandom()
{
	int tResult = rand() % 10;

	log("rand result: %d", tResult);

	return tResult;
}

void SceneBox2D::menuCloseCallback(Ref * pSender)
{
	this->unscheduleUpdate();




	//이벤트리스너를 해지한다.
	_eventDispatcher->removeEventListener(mpListener);



	if (NULL != mpb2World)
	{
		delete mpb2World;
		mpb2World = NULL;
	}



	Director::getInstance()->popScene();
}

void SceneBox2D::onClickBtnGoMove(Ref * pSender)
{
	b2Body *tpBody = mpb2World->GetBodyList();





	//이 값은 어떤 것을 기준으로 삼아 결정하면 좋은가?
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(60));
	double tFScalar = 1000.0f;



	double tFX = tFScalar * 1;
	double tFY = tFScalar*tTrigonoV;

	//한방?(한step에서)에 힘을 가한다.
	tpBody->ApplyLinearImpulse(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);

	//단위시간 1초 동안 힘을 가한다.
	//tpBody->ApplyForce(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);
	//tpBody->ApplyForceToCenter(b2Vec2(tFX, tFY), true);
	//tpBody->ApplyTorque(2.0f, true);
}

bool SceneBox2D::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	return true;
}

void SceneBox2D::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
}

void SceneBox2D::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();






	//dipslay debug
	char szTemp[512];
	memset(szTemp, 0, 512);

	sprintf(szTemp, "Touch point: %f, %f",
		tTouchPos.x, tTouchPos.y);

	if (NULL != mplblDebug)
	{
		mplblDebug->setString(szTemp);
	}




	Sprite *tpSprite = Sprite::create("actor.png");
	tpSprite->retain();



	mSpriteVec.pushBack(tpSprite);

	tpSprite->setPosition(tTouchPos);
	//tpSprite->setPosition( Vec2(300,100) );
	this->addChild(tpSprite);




	b2BodyDef tBodyDef;

	tBodyDef.type = b2_dynamicBody;
	tBodyDef.position.Set(tTouchPos.x / PTM_RATIO, tTouchPos.y / PTM_RATIO);
	tBodyDef.userData = tpSprite;
	//tBodyDef.userData = nullptr;

	b2Body *tpBody = mpb2World->CreateBody(&tBodyDef);

	//질량은 어떻게 결정되는가?
	b2CircleShape tCircle;
	tCircle.m_radius = 1.5f;//1.0f;



	b2FixtureDef tFixtureDef;
	tFixtureDef.shape = &tCircle;
	tFixtureDef.density = 1.0f;
	tFixtureDef.friction = 0.5f;//0.2f;
	tFixtureDef.restitution = 0.5f;//0.7f;


	tpBody->CreateFixture(&tFixtureDef);

}

void SceneBox2D::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	kmGLPushMatrix();
	mpb2World->DrawDebugData();
	kmGLPopMatrix();

	/*_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(SceneBox2D::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);*/
}

void SceneBox2D::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	mpb2World->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
