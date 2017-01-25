#include "b2Bullet.h"
#include "b2Custom\b2Util.h"
#include "b2Custom\exam\b2Tag.h"

bool b2Bullet::init()
{
	if (!b2Node::init())
	{
		return false;
	}

	Setb2Tag(TAG_BULLET);
	SetWorldBoxCollision(true);
	auto tSprite = Sprite::create("actor.png");
	this->addChild(tSprite, 0);

	return true;
}

void b2Bullet::CreateBody(b2World * world)
{
	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	b2Vec2 tPos = b2Util::ConvertTob2Vec(this->getPosition());
	tBodyDef.position.Set(tPos.x, tPos.y);
	tBodyDef.userData = this;
	mpBody = world->CreateBody(&tBodyDef);

	b2CircleShape tCircle;
	tCircle.m_radius = 1.0f;
	b2FixtureDef tFixDef;
	tFixDef.shape = &tCircle;
	tFixDef.density = 1.0f;
	tFixDef.friction = 0.5f;
	tFixDef.restitution = 0.0f;

	mpBody->CreateFixture(&tFixDef);
}

void b2Bullet::OnCollisionEnter(b2CollisionData * data)
{
	if (data->otherNode == nullptr )
	{
		if (data->worldBoxTag == WorldBoxTag::TAG_BOTTOM)
		{
			log("collision bottom worldbox");
			this->SetDestroyTag();
		}
		else
		{
			log("[%d] worldbox", data->worldBoxTag);
		}
	}
	else if (data->otherNode->Getb2Tag() == TAG_BULLET)
	{
		//data->otherNode->SetDestroyTag();
		log("collision bullet");
	}
}

void b2Bullet::OnCollisionStay(b2CollisionData * data)
{

}

void b2Bullet::OnCollisionExit(b2CollisionData * data)
{

}


