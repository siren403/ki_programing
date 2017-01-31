#include "b2RopeTarget.h"
#include "b2Tag.h"

bool b2RopeTarget::init()
{
	if (!b2Node::init())
	{
		return false;
	}

	return true;
}


void b2RopeTarget::CreateBody(b2World * world)
{
	b2BodyDef tBodyDef;
	tBodyDef.type = b2_kinematicBody;
	mpBody = CreateBodyByNodeSync(world, &tBodyDef);
	b2PolygonShape tShape;
	tShape.SetAsBox(0.8, 0.5);
	b2FixtureDef tFixDef;
	tFixDef.shape = &tShape;
	mpBody->CreateFixture(&tFixDef);
}

void b2RopeTarget::OnCollisionEnter(b2CollisionData * data)
{
	if (data->otherNode->Getb2Tag() == TAG_BULLET)
	{
		//mpBody->GetWorld()->DestroyJoint(mpRope);
		mpRope = nullptr;
	}
}

void b2RopeTarget::OnCollisionStay(b2CollisionData * data)
{

}

void b2RopeTarget::OnCollisionExit(b2CollisionData * data)
{

}

void b2RopeTarget::AttachTarget(b2Node * tTargetNode)
{
	/*b2RopeJointDef tRopeDef;

	tRopeDef.bodyA = mpBody;
	tRopeDef.bodyB = tTargetNode->GetBody();
	tRopeDef.localAnchorA = b2Vec2(0.0f, -0.5f);
	tRopeDef.localAnchorB = b2Vec2(0.0f, 2.0f);
	tRopeDef.maxLength = 3.5f;
	tRopeDef.collideConnected = true;

	mpRope = (b2RopeJoint *)mpBody->GetWorld()->CreateJoint(&tRopeDef);*/



	b2BodyDef tRopeBodyDef;
	tRopeBodyDef.position.x = 9;
	tRopeBodyDef.position.y = 20;
	tRopeBodyDef.type = b2_kinematicBody;
	b2Body * tRopeBody = mpBody->GetWorld()->CreateBody(&tRopeBodyDef);
	mpRopeHead = tRopeBody;

	b2PolygonShape tShape;
	tShape.SetAsBox(2, 0.5);
	b2FixtureDef tFixDef;
	tFixDef.shape = &tShape;
	tFixDef.density = 0;
	tFixDef.friction = 0.5;
	tFixDef.restitution = 0.2;

	tRopeBody->CreateFixture(&tFixDef);

	b2Body * tPrevBody = tRopeBody;
	b2RevoluteJointDef tRevoluteDef;
	tRopeBodyDef.type = b2_dynamicBody;
	
	//// rope
	for (int i = 1; i <= 10; i++) 
	{

		tRopeBodyDef.position.y -= 1;

		tShape.SetAsBox(0.1, 0.5);
		tFixDef.density = 100;
		tFixDef.friction = 0.5;
		tFixDef.restitution = 0.2;
		tRopeBody = mpBody->GetWorld()->CreateBody(&tRopeBodyDef);
		tRopeBody->CreateFixture(&tFixDef);
		// joint
		tRevoluteDef.Initialize(tPrevBody, tRopeBody,b2Vec2(tRopeBodyDef.position.x, tRopeBodyDef.position.y + 0.5));
		mpBody->GetWorld()->CreateJoint(&tRevoluteDef);
		tPrevBody = tRopeBody;
	}

	tRopeBodyDef.position.y--;
	/*tShape.SetAsBox(0.5, 0.5);
	tFixDef.density = 2;
	tFixDef.friction = 0.5;
	tFixDef.restitution = 0.2;
	tRopeBody = mpBody->GetWorld()->CreateBody(&tRopeBodyDef);
	tRopeBody->CreateFixture(&tFixDef);
*/
	tTargetNode->GetBody()->SetTransform(b2Vec2(tRopeBodyDef.position.x, tRopeBodyDef.position.y - 2),0);
	tRevoluteDef.Initialize(tPrevBody, tTargetNode->GetBody(), b2Vec2(tRopeBodyDef.position.x, tRopeBodyDef.position.y));
	mpBody->GetWorld()->CreateJoint(&tRevoluteDef);

}
