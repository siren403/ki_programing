#include "b2Block.h"
#include "b2Tag.h"
#include "b2Custom\b2Util.h"


bool b2Block::init()
{
	if (!b2Node::init())
	{
		return false;
	}

	Setb2Tag(TAG_BLOCK);
	mSprite = Sprite::create("grossini.png");
	this->addChild(mSprite, 0);
	return true;
}

void b2Block::CreateBody(b2World * world)
{
	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	mpBody = this->CreateBodyByNodeSync(world, &tBodyDef);


	b2PolygonShape tBoxShape;
	b2Vec2 tBoxSize = b2Util::ConvertTob2Vec(
		mSprite->getContentSize().width * 0.2,
		mSprite->getContentSize().height * 0.9);
	tBoxShape.SetAsBox(tBoxSize.x, tBoxSize.y);

	b2FixtureDef tFixDef;
	tFixDef.shape = &tBoxShape;
	tFixDef.density = 1.0f;
	tFixDef.friction = 0.5f;

	mpBody->CreateFixture(&tFixDef);
}

void b2Block::OnCollisionEnter(b2CollisionData * data)
{
	if (data->otherNode->Getb2Tag() == TAG_BULLET)
	{
		log("Enter Bullet");
	}
}

void b2Block::OnCollisionStay(b2CollisionData * data)
{
}

void b2Block::OnCollisionExit(b2CollisionData * data)
{
}
