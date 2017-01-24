#include "SceneBox2dJoint.h"

using namespace std;

Scene * SceneBox2dJoint::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneBox2dJoint::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);


	// return the scene
	return scene;
}

bool SceneBox2dJoint::init()
{
	if (!Layer::init())
	{
		return false;
	}

	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");


	return true;
}

void SceneBox2dJoint::update(float dt)
{
}

void SceneBox2dJoint::onEnter()
{
	Layer::onEnter();

	auto tListener = EventListenerTouchOneByOne::create();
	tListener->setSwallowTouches(true);
	tListener->onTouchBegan = CC_CALLBACK_2(SceneBox2dJoint::onTouchBegan, this);
	tListener->onTouchMoved = CC_CALLBACK_2(SceneBox2dJoint::onTouchMoved, this);
	tListener->onTouchEnded = CC_CALLBACK_2(SceneBox2dJoint::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tListener, this);

	createPhysicsWorld();

	bDrag = false;
	//================================================
	//마우스 조인트 바디 생성 후 월드 추가
	gbody = this->addNewSprite(Point(0, 0), Size(0, 0), b2_staticBody, "blocks.png", 0);
	this->addNewSprite(Point(240, 260), Size(32, 32), b2_dynamicBody, "test", 0);
	//================================================
	b2Body * body1 = this->addNewSprite(Point(240, 260), Size(32, 32), b2_staticBody, "test", 0);
	b2Body * body2 = this->addNewSprite(Point(140, 260), Size(32, 32), b2_dynamicBody, "test", 0);

	b2RevoluteJointDef tDef;
	b2RevoluteJoint * tRevoluteJoint = nullptr;

	tDef.Initialize(body1, body2, body1->GetPosition());
	//case 0
	//tDef.enableLimit = true;
	//tDef.lowerAngle = -90;
	//tDef.upperAngle = 0;
	//case 1
	tDef.enableMotor = true;
	tDef.motorSpeed = 5; // radians per second. 1 radian = 180/pi degrees
	tDef.maxMotorTorque = 20;//100; // 회전력

	tRevoluteJoint = (b2RevoluteJoint *)mpWorld->CreateJoint(&tDef);


	//================================================
	b2WeldJointDef tWeldJointDef;
	b2Body * body3 = this->addNewSprite(Point(200, mWinSize.height / 2),
		Size(60, 60), b2_dynamicBody, "test", 0);
	b2Body *body4 = this->addNewSprite(Point(200 + 2, mWinSize.height / 2 + 2), Size(40, 40),
		b2_dynamicBody, "CloseNormal.png", 0);
	tWeldJointDef.Initialize(body3, body4, body3->GetPosition());

	mpWorld->CreateJoint(&tWeldJointDef);

	//================================================
	float start = 100;
	for (int i = 0; i < 10; i++)
	{
		b2Body * body5 = this->addNewSprite(Point(start + 48 * i, 10), Size(4, 20),
			b2_staticBody, nullptr, 0);
		b2Body * body6 = this->addNewSprite(Point(start + 48 * i, 10), Size(44, 20),
			b2_dynamicBody, nullptr, 0);

		b2PrismaticJointDef tPrismaticJointDef;

		tPrismaticJointDef.Initialize(body5, body6, body5->GetPosition(), b2Vec2(0.0, 1.0));
		tPrismaticJointDef.collideConnected = false;
		tPrismaticJointDef.lowerTranslation = 0;//최소 감소 치
		tPrismaticJointDef.upperTranslation = 3;//최고 상승 치,리미트 해제 시 의미 없음
		tPrismaticJointDef.enableLimit = true;

		tPrismaticJointDef.enableMotor = true;
		tPrismaticJointDef.motorSpeed = 3;
		tPrismaticJointDef.maxMotorForce = 900;


		b2PrismaticJoint * tPrismaticJoint = (b2PrismaticJoint*)mpWorld->CreateJoint(&tPrismaticJointDef);
	}

	//================================================

	b2Body * body7 = this->addNewSprite(Point(440, 480), Size(40, 40),
		b2_staticBody, "test", 0);
	b2Body * body8 = this->addNewSprite(Point(540, 480), Size(40, 40),
		b2_dynamicBody, "test", 0);


	b2DistanceJointDef tDistanceJointDef;
	tDistanceJointDef.Initialize(body7, body8,
		b2Vec2(body7->GetPosition().x, body7->GetPosition().y),
		b2Vec2(body8->GetPosition().x, body8->GetPosition().y));
	
	mpWorld->CreateJoint(&tDistanceJointDef);

	//================================================

	this->scheduleUpdate();

	this->runAction(ScaleTo::create(1, 0.99));
}

void SceneBox2dJoint::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	destroyPhysicsWorld();

	this->unscheduleUpdate();

	Layer::onExit();
}



void SceneBox2dJoint::createPhysicsWorld()
{
	mWinSize = Director::getInstance()->getWinSize();


	b2Vec2 tGravity = b2Vec2(0.0f, -30.0f);

	mpWorld = new b2World(tGravity);
	mpWorld->SetAllowSleeping(true);
	mpWorld->SetContinuousPhysics(true);

	b2BodyDef tGroundBodyDef;
	tGroundBodyDef.position.Set(0, 0);
	tGroundBodyDef.type = b2_staticBody;

	b2Body * tpGroundBody = mpWorld->CreateBody(&tGroundBodyDef);

	b2EdgeShape tGroundEdge;

	b2FixtureDef tBoxShapeDef;
	tBoxShapeDef.shape = &tGroundEdge;

	tGroundEdge.Set(b2Vec2(0, 0), b2Vec2(0, mWinSize.height / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//top
	tGroundEdge.Set(b2Vec2(0, mWinSize.height / PTM_RATIO),
		b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//right
	tGroundEdge.Set(b2Vec2(mWinSize.width / PTM_RATIO, mWinSize.height / PTM_RATIO),
		b2Vec2(mWinSize.width / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//bottom
	tGroundEdge.Set(b2Vec2(0, 0),b2Vec2(mWinSize.width / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	this->schedule(CC_SCHEDULE_SELECTOR(SceneBox2dJoint::updatePhysicsWorld));


	mpContactListener = new ContactListener();
	mpWorld->SetContactListener((b2ContactListener *)mpContactListener);

	mDebugDraw = new GLESDebugDraw(PTM_RATIO);
	mpWorld->SetDebugDraw(mDebugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	mDebugDraw->SetFlags(flags);

}
void SceneBox2dJoint::updatePhysicsWorld(float dt)
{
	if (nullptr == mpWorld)
	{
		return;
	}
	
	int tVelocityIterations = 8;
	int tPositionIterations = 3;

	mpWorld->Step(dt, tVelocityIterations, tPositionIterations);

	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();

			if (nullptr != tpSprite)
			{
				tpSprite->setPosition(Vec2(tpBody->GetPosition().x * PTM_RATIO,
					tpBody->GetPosition().y *PTM_RATIO));

				tpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(tpBody->GetAngle()));

			}
		}
	}

}

void SceneBox2dJoint::destroyPhysicsWorld()
{
	if (nullptr != mpWorld)
	{
		delete mpWorld;
		mpWorld = nullptr;
	}
}

void SceneBox2dJoint::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	kmGLPushMatrix();
	mpWorld->DrawDebugData();
	kmGLPopMatrix();
}

b2Body * SceneBox2dJoint::addNewSprite(Point point, Size size, b2BodyType bodytype, const char * spriteName, int type)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName)
	{
		if (strcmp(spriteName, "test") == 0)
		{
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture,Rect(32 * idx, 32 * idy, 32, 32));
		
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else
		{
			Sprite * sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}

	//body 생성
	b2Body * body = mpWorld->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0)
	{
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
	}
	else
	{
		circle.m_radius = (size.width / 2) / PTM_RATIO;
		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body * SceneBox2dJoint::getBodyAtTab(Point p)
{
	b2Fixture * fix;
	for (b2Body *b = mpWorld->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			if (b->GetType() == b2_staticBody)
				continue;

			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO)))
			{
				return b;
			}
		}
	}
	return nullptr;
}

void SceneBox2dJoint::onDraw(const Mat4 & transform, uint32_t flags)
{

}

bool SceneBox2dJoint::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	if (b2Body * b = this->getBodyAtTab(tTouchPos))
	{
		dragBody = b;
		bDrag = true;

		b2MouseJointDef tDef;
		tDef.bodyA = gbody;
		tDef.bodyB = dragBody;
		tDef.target.Set(dragBody->GetPosition().x, dragBody->GetPosition().y);
		tDef.maxForce = 300.0 * dragBody->GetMass();

		mpMouseJoint = (b2MouseJoint *)mpWorld->CreateJoint(&tDef);
	}

	return true;
}

void SceneBox2dJoint::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	if (bDrag)
	{
		mpMouseJoint->SetTarget(b2Vec2(tTouchPos.x / PTM_RATIO, tTouchPos.y / PTM_RATIO));
	}
}

void SceneBox2dJoint::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	if (bDrag)
	{
		mpWorld->DestroyJoint(mpMouseJoint);
		mpMouseJoint = nullptr;

		dragBody->SetAwake(true);
	}
	bDrag = false;
}