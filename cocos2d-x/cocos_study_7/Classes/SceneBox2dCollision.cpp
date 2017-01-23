#include "SceneBox2dCollision.h"

using namespace std;

Scene * SceneBox2DCollision::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneBox2DCollision::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);


	// return the scene
	return scene;
}

bool SceneBox2DCollision::init()
{
	if (!Layer::init())
	{
		return false;
	}


	


	mpLayerUI = Layer::create();
	this->addChild(mpLayerUI, 100);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mpSprBtn = Sprite::create("btn_push.png");
	mpSprBtn->setPosition(Vec2(700, 240));
	mpLayerUI->addChild(mpSprBtn, 100);


	mpLabelDebug = Label::createWithTTF("DEBUG: ", "fonts/BMJUA_ttf.ttf", 18);
	mpLabelDebug->setOpacity(128);
	mpLabelDebug->setAnchorPoint(Vec2(0, 0));
	mpLabelDebug->setPosition(Vec2(50, 50));

	mpLayerUI->addChild(mpLabelDebug, 100);


	return true;
}

void SceneBox2DCollision::update(float dt)
{
}

void SceneBox2DCollision::onEnter()
{
	Layer::onEnter();

	auto tListener = EventListenerTouchOneByOne::create();
	tListener->setSwallowTouches(true);
	tListener->onTouchBegan = CC_CALLBACK_2(SceneBox2DCollision::onTouchBegan, this);
	tListener->onTouchMoved = CC_CALLBACK_2(SceneBox2DCollision::onTouchMoved, this);
	tListener->onTouchEnded = CC_CALLBACK_2(SceneBox2DCollision::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tListener, this);

	createPhysicsWorld();

	this->scheduleUpdate();

}

void SceneBox2DCollision::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	destroyPhysicsWorld();

	this->unscheduleUpdate();

	Layer::onExit();
}

bool SceneBox2DCollision::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	return true;
}

void SceneBox2DCollision::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
}

void SceneBox2DCollision::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	if ((tTouchPos.x >= 700 - 40 && tTouchPos.x <= 700 + 40) &&
		(tTouchPos.y >= 240 - 40 && tTouchPos.y <= 240 + 40))
	{
		doFire();
		return;
	}

	log("Touch point : %f, %f", tTouchPos.x, tTouchPos.y);

	Sprite *tpSprite = Sprite::create("actor.png");

	tpSprite->setPosition(tTouchPos);
	this->addChild(tpSprite);

	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	tBodyDef.position.Set(tTouchPos.x / PTM_RATIO, tTouchPos.y / PTM_RATIO);
	tBodyDef.userData = tpSprite;
	b2Body * tpBody = mpWorld->CreateBody(&tBodyDef);

	b2CircleShape tCircle;
	tCircle.m_radius = 1.0f;

	b2FixtureDef tFixtureDef;
	tFixtureDef.shape = &tCircle;
	tFixtureDef.density = 1.0f;
	tFixtureDef.friction = 0.5f;
	tFixtureDef.restitution = 0.0f;

	tpBody->CreateFixture(&tFixtureDef);


	/*
	//사각형을 만듦( 사각형도 폴리곤에 속하므로 b2PolygonShape로 만듦

	b2PolygonShape tPolygonShape;

	tPolygonShape.SetAsBox(0.5f, 0.5f); //a 4x2 rectangle

	b2FixtureDef tFixtureDef;

	tFixtureDef.shape       = &tPolygonShape;
	tFixtureDef.density     = 1.0f;
	tFixtureDef.friction    = 0.5f;//0.2f;
	tFixtureDef.restitution = 0.0f;//0.7f;


	tpBody->CreateFixture(&tFixtureDef);
	*/

	//질량은 어떻게 결정되는가?
	//원의 경우에 반지름이 1인 경우 3.14,
	//사각형의 경우에는 0.5, 0.5 ( 1x1 ) 의 경우 1
	//Shape의 크기에 기반하는 것으로 보인다.
	float32 tMass = tpBody->GetMass();
	log("tMass : %f", tMass);

	/*
	b2MassData tData;
	tData.mass = 1.0f;
	tpBody->SetMassData(&tData);

	tMass = tpBody->GetMass();
	log("==tMass: %f", tMass);
	*/

	//카메라가 이 Layer를 보도록 설정한다.
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create(this, myBoundary));

}

void SceneBox2DCollision::doFire()
{
	mpCurBody = mpWorld->GetBodyList();

	if (nullptr == (Sprite *)(mpCurBody->GetUserData()))
	{
		return;
	}

	//방향은 각도 70도, 힘의 크기는 100의 경우를 보이고 있다.
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(70));
	double tFScalar = 100.0f;

	//닮은 삼각형임을 이용하여 각 축의 힘의 크기를 구하였다.
	double tFX = tFScalar / sqrt((tTrigonoV*tTrigonoV + 1));
	double tFY = sqrt(tFScalar * tFScalar -
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))*
		(tFScalar / sqrt(1 + tTrigonoV*tTrigonoV))
	);

	//주어진 벡터만큼의 힘을 가하는 코드이다.
	mpCurBody->ApplyLinearImpulse(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);

	//메인카메라가 해당객체를 따라다니게 하는 액션이다.
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create((Sprite *)(mpCurBody->GetUserData()), myBoundary));

}

void SceneBox2DCollision::createPhysicsWorld()
{
	mWinSize = Director::getInstance()->getWinSize();


	//중력값을 설정하고, 중력값을 바탕으로 물리세계를 만든다.
	b2Vec2 tGravity = b2Vec2(0.0f, -30.0f);

	mpWorld = new b2World(tGravity);
	mpWorld->SetAllowSleeping(true);
	mpWorld->SetContinuousPhysics(true);

	//물리세계의 경계를 위해 Physical Body들을 staticBody로 만든다.
	b2BodyDef tGroundBodyDef;
	tGroundBodyDef.position.Set(0, 0);
	tGroundBodyDef.type = b2_staticBody;

	b2Body * tpGroundBody = mpWorld->CreateBody(&tGroundBodyDef);

	b2EdgeShape tGroundEdge;
	b2FixtureDef tBoxShapeDef;
	tBoxShapeDef.shape = &tGroundEdge;

	//left
	tGroundEdge.Set(b2Vec2(0, 0), b2Vec2(0, mWinSize.height * 2 / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//top
	tGroundEdge.Set(b2Vec2(0, mWinSize.height * 2 / PTM_RATIO),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, mWinSize.height * 2 / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//right
	tGroundEdge.Set(b2Vec2(mWinSize.width * 2 / PTM_RATIO, mWinSize.height * 2 / PTM_RATIO),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//bottom
	tGroundEdge.Set(b2Vec2(0, 0),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//물리세계의 정보들을 갱신하기 위한 루프를 만든다.
	//this->schedule(schedule_selector(SceneBox2DCollision::updatePhysicsWorld));
	this->schedule(CC_SCHEDULE_SELECTOR(SceneBox2DCollision::updatePhysicsWorld));


	//물리세계에서 일어나는 충돌들을 감지하기 위한 리스너를 만든다.
	mpContactListener = new ContactListener();
	mpWorld->SetContactListener((b2ContactListener *)mpContactListener);

	//debug
	// 디버그 드로잉 설정
	// 적색 : 현재 물리 운동을 하는 것
	// 회색 : 현재 물리 운동량이 없는 것
	mDebugDraw = new GLESDebugDraw(PTM_RATIO);
	mpWorld->SetDebugDraw(mDebugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	mDebugDraw->SetFlags(flags);

}

void SceneBox2DCollision::destroyPhysicsWorld()
{
	//물리 객체들을 삭제한다.
	//물리 객체에 연결된 스프라이트(노드)도 삭제해야 한다.


	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();
			this->removeChild(tpSprite);

			mpWorld->DestroyBody(tpBody);
		}
	}

	//물리세계를 파괴한다.
	if (nullptr != mpWorld)
	{
		delete mpWorld;
		mpWorld = nullptr;
	}


}

void SceneBox2DCollision::updatePhysicsWorld(float dt)
{
	if (nullptr == mpWorld)
	{
		return;
	}
	//http://cafe.naver.com/cocos2dxusers/25620
	// velocityIterations : 바디들을 정상적으로 이동시키기 위해서 필요한 충돌들을 반복적으로 계산
	// positionIterations : 조인트 분리와, 겹침현상을 줄이기 위해서 바디의 위치를 반복적으로 적용
	// 값이 클수록 정확한 연산이 가능하지만 성능이 떨어진다.

	//매뉴얼 추천값
	int tVelocityIterations = 8;
	int tPositionIterations = 3;

	//Step메소드의 역할은 무엇인가? 물리기반 세계를 진행한다.
	mpWorld->Step(dt, tVelocityIterations, tPositionIterations);

	//아래 구문은 무엇을 하는 것인가?
	//물리결과에 기반하여 Sprite의 위치와 회전값을 갱신하는 것이다.
	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();

			if (nullptr != tpSprite)
			{
				//물리기반 세계의 좌표에서 픽셀단위 좌표계로 값을 변환해준다.
				tpSprite->setPosition(Vec2(tpBody->GetPosition().x * PTM_RATIO,
					tpBody->GetPosition().y *PTM_RATIO));

				//각을 라디안에서 도 단위로 변환한다.
				//-1을 곱하는 이유는 무엇인가?
				tpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(tpBody->GetAngle()));

			}
		}
	}
	
	//destroy physical body
	std::vector<b2Body *> tDestroyVec;
	std::vector<SContacts>::iterator tIterator;


	//충돌 감지 리스트에 담긴 Physical Body들을 가져와 삭제대상목록에 넣는다.
	for (tIterator = mpContactListener->mSContacts.begin();
		tIterator != mpContactListener->mSContacts.end(); ++tIterator)
	{
		SContacts tSContacts = *tIterator;

		b2Body *tpBodyA = tSContacts.fixtureA->GetBody();
		b2Body *tpBodyB = tSContacts.fixtureB->GetBody();

		if (tpBodyA->GetUserData() != nullptr && tpBodyB->GetUserData() != nullptr)
		{
			Sprite * tpSpriteA = (Sprite *)tpBodyA->GetUserData();
			Sprite * tpSpriteB = (Sprite *)tpBodyB->GetUserData();

			if (nullptr != tpSpriteA && nullptr != tpSpriteB)
			{
				if (std::find(tDestroyVec.begin(), tDestroyVec.end(), tpBodyB) == tDestroyVec.end())
				{
					tDestroyVec.push_back(tpBodyB);
				}

				if (std::find(tDestroyVec.begin(), tDestroyVec.end(), tpBodyA) == tDestroyVec.end())
				{
					tDestroyVec.push_back(tpBodyA);
				}
			}
		}
	}

	//삭제대상 목록에 있는 Physical Body 들을 삭제한다.
	std::vector<b2Body *>::iterator tIterator_0;
	for (tIterator_0 = tDestroyVec.begin(); tIterator_0 != tDestroyVec.end(); ++tIterator_0)
	{
		b2Body * tpBody = *tIterator_0;
		if (tpBody->GetUserData() != nullptr)
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();
			this->removeChild(tpSprite, true);

			tpSprite = NULL;
		}

		mpWorld->DestroyBody(tpBody);
	}

}

void SceneBox2DCollision::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	kmGLPushMatrix();
	mpWorld->DrawDebugData();
	kmGLPopMatrix();
}

void SceneBox2DCollision::onDraw(const Mat4 & transform, uint32_t flags)
{
}

