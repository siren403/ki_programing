#include "b2Layer.h"
#include "b2LayerContactListener.h"
#include "b2Util.h"
#include "b2WorldBoxData.h"

Scene * b2Layer::createScene()
{
	auto scene = Scene::create();
	auto layer = b2Layer::create();
	scene->addChild(layer);
	return scene;
}

bool b2Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	mWinSize = Director::getInstance()->getWinSize();
	if (mWorldSizeRatio == Vec2::ZERO)
	{
		mWorldSize = mWinSize;
	}
	else
	{
		mWorldSize = Size(mWinSize.width*mWorldSizeRatio.x, mWinSize.height*mWorldSizeRatio.y);
	}

	if (mGravity == b2Vec2(0, 0))
	{
		mGravity = b2Vec2(0.0f, -30.0f);
	}
	
	mpWorld = new b2World(mGravity);
	//휴식 상태의 바디들을 sleep으로 할 것인지 결정
	mpWorld->SetAllowSleeping(true);
	//지속적인 물리작용(?)을 할 것인지 결정 
	mpWorld->SetContinuousPhysics(true);
	mpWorld->SetContactListener(new b2LayerContactListener());

	mIsDebug = true;
	if (mIsDebug)
	{
		mpDebugDraw = new GLESDebugDraw(b2Util::GetRatio());
		mpWorld->SetDebugDraw(mpDebugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		mpDebugDraw->SetFlags(flags);
	}


	b2BodyDef tGroundBodyDef;
	tGroundBodyDef.position.Set(0, 0);
	tGroundBodyDef.type = b2_staticBody;

	b2Body * tpGroundBody = mpWorld->CreateBody(&tGroundBodyDef);

	b2EdgeShape tGroundEdge;

	b2FixtureDef tBoxShapeDef;
	tBoxShapeDef.shape = &tGroundEdge;

	b2Vec2 tLeftBottom = b2Util::ConvertTob2Vec(mWorldBoxMargin, mWorldBoxMargin);
	b2Vec2 tLeftTop = b2Util::ConvertTob2Vec(mWorldBoxMargin, mWorldSize.height - mWorldBoxMargin);
	b2Vec2 tRightBottom = b2Util::ConvertTob2Vec(mWorldSize.width - mWorldBoxMargin, mWorldBoxMargin);
	b2Vec2 tRightTop = b2Util::ConvertTob2Vec(mWorldSize.width - mWorldBoxMargin, mWorldSize.height - mWorldBoxMargin);


	//left
	tGroundEdge.Set(tLeftBottom, tLeftTop);
	tBoxShapeDef.userData = new b2WorldBoxData(WorldBoxTag::TAG_LEFT);
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//top
	tGroundEdge.Set(tLeftTop, tRightTop);
	tBoxShapeDef.userData = new b2WorldBoxData(WorldBoxTag::TAG_TOP);
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//right
	tGroundEdge.Set(tRightTop, tRightBottom);
	tBoxShapeDef.userData = new b2WorldBoxData(WorldBoxTag::TAG_RIGHT);
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//bottom
	tGroundEdge.Set(tLeftBottom, tRightBottom);
	tBoxShapeDef.userData = new b2WorldBoxData(WorldBoxTag::TAG_BOTTOM);
	tpGroundBody->CreateFixture(&tBoxShapeDef);


	this->schedule(CC_SCHEDULE_SELECTOR(b2Layer::updatePhysics));

	return true;
}

void b2Layer::onEnter()
{
	Layer::onEnter();
	this->AddTouchListener();
}

void b2Layer::onExit()
{
	CC_SAFE_DELETE(mpWorld);
	_eventDispatcher->removeEventListenersForTarget(this);
	Layer::onExit();
}

void b2Layer::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	kmGLPushMatrix();
	mpWorld->DrawDebugData();
	kmGLPopMatrix();
}

void b2Layer::Addb2Child(b2Node * node)
{
	node->CreateBody(this->mpWorld);
	this->addChild(node);
}

void b2Layer::Addb2Child(b2Node * node, int localZorder)
{
	node->CreateBody(this->mpWorld);
	this->addChild(node, localZorder);
}

void b2Layer::AddTouchListener()
{
	auto tListener = EventListenerTouchOneByOne::create();
	tListener->setSwallowTouches(true);
	tListener->onTouchBegan = CC_CALLBACK_2(b2Layer::onTouchBegan, this);
	tListener->onTouchMoved = CC_CALLBACK_2(b2Layer::onTouchMoved, this);
	tListener->onTouchEnded = CC_CALLBACK_2(b2Layer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tListener, this);
}

void b2Layer::updatePhysics(float dt)
{
	if (nullptr == mpWorld)
	{
		return;
	}

	int tVelocityIterations = 8;
	int tPositionIterations = 3;

	mpWorld->Step(dt, tVelocityIterations, tPositionIterations);

	//물리결과에 기반하여 Sprite의 위치와 회전값을 갱신하는 것이다.
	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();

			if (nullptr != tpSprite)
			{
				//물리기반 세계의 좌표에서 픽셀단위 좌표계로 값을 변환해준다.
				tpSprite->setPosition(b2Util::ConvertToVec(tpBody->GetPosition()));

				//각을 라디안에서 도 단위로 변환한다.
				//-1을 곱하는 이유는 무엇인가?
				tpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(tpBody->GetAngle()));

			}
		}
	}

	b2Node * tb2Node = nullptr;
	std::vector<b2Node *> tDestroyb2Node;
	for (Node * node : this->getChildren())
	{
		tb2Node = (b2Node *)node;
		if (tb2Node != nullptr && tb2Node->Getb2Tag() == b2Util::GetDestroyTag())
		{
			tDestroyb2Node.push_back(tb2Node);
		}
	}
	std::vector<b2Node *>::iterator tIterator;
	for (tIterator = tDestroyb2Node.begin(); tIterator != tDestroyb2Node.end(); ++tIterator)
	{
		tb2Node = *tIterator;
		mpWorld->DestroyBody(tb2Node->GetBody());
		this->removeChild(tb2Node, true);
	}
}
