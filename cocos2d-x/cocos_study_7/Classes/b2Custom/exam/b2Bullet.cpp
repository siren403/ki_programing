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
	mpSprite = Sprite::create("actor.png");
	mpSprite->setScale(0.3);
	this->addChild(mpSprite, 0);

	return true;
}

void b2Bullet::CreateBody(b2World * world)
{
	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	tBodyDef.angularDamping = 10.0f;
	mpBody = this->CreateBodyByNodeSync(world, &tBodyDef);

	//b2PolygonShape tShape;
	//tShape.SetAsBox(1.3f, 0.5f, b2Vec2(1.3, 0), 0);//1.3, 0.5
	b2CircleShape tShape;
	tShape.m_radius = mpSprite->getContentSize().width /6/ b2Util::GetRatio();
	b2FixtureDef tFixDef;
	tFixDef.shape = &tShape;
	tFixDef.density = 5.0f;//밀도
	tFixDef.friction = 0.15f;//마찰
	tFixDef.restitution = 0.3f;//반발

	mpBody->CreateFixture(&tFixDef);

}

void b2Bullet::OnCollisionEnter(b2CollisionData * data)
{
	if (data->otherNode == nullptr )
	{
		if (data->worldBoxTag == WorldBoxTag::TAG_BOTTOM)
		{
			log("collision bottom worldbox");
			//this->SetDestroyTag();
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


