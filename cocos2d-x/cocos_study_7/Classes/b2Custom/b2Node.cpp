#include "b2Node.h"
#include "b2Util.h"


bool b2Node::init()
{
	if (!Node::init())
	{
		return false;
	}


	return true;
}
void b2Node::OnCollisionEnter(b2CollisionData * data)
{
	log("[%d]to[%d] Collision Enter", mb2Tag, data->otherNode->Getb2Tag());
}

void b2Node::OnCollisionStay(b2CollisionData * data)
{
	//log("[%d] Collision Stay", mb2Tag);
}

void b2Node::OnCollisionExit(b2CollisionData * data)
{
	log("[%d]to[%d] Collision Exit", mb2Tag, data->otherNode->Getb2Tag());
}

void b2Node::CreateBody(b2World * world)
{
	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	mpBody = CreateBodyByNodeSync(world, &tBodyDef);

	b2FixtureDef tFixDef;
	b2CircleShape tCircle;
	tCircle.m_radius = 1.0f;
	tFixDef.shape = &tCircle;
	tFixDef.density = 1.0f;
	tFixDef.friction = 0.5f;
	tFixDef.restitution = 0.5f;

	mpBody->CreateFixture(&tFixDef);
}
b2Body * b2Node::CreateBodyByNodeSync(b2World * world, b2BodyDef * tBodyDef)
{
	b2Vec2 tPos = b2Util::ConvertTob2Vec(this->getPosition());
	tBodyDef->position.Set(tPos.x, tPos.y);
	tBodyDef->angle = CC_DEGREES_TO_RADIANS(-1 * this->getRotation());
	tBodyDef->userData = this;
	return world->CreateBody(tBodyDef);

}
b2Body * b2Node::GetBody()
{
	return mpBody;
}

void b2Node::Setb2Tag(int tag)
{
	mb2Tag = tag;
}

int b2Node::Getb2Tag()
{
	return mb2Tag;
}

void b2Node::SetDestroyTag()
{
	mb2Tag = b2Util::GetDestroyTag();
}

bool b2Node::IsDestroyTag()
{
	return mb2Tag == b2Util::GetDestroyTag();
}

bool b2Node::IsWorldBoxCollision()
{
	return mIsWorldBoxCollision;
}

void b2Node::SetWorldBoxCollision(bool isCollision)
{
	mIsWorldBoxCollision = isCollision;
}
