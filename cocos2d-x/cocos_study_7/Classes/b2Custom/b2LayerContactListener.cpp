#include "b2LayerContactListener.h"
#include "b2Util.h"

void b2LayerContactListener::OnNodeCallback(b2Contact * contact, ContactCallback callback)
{
	b2Fixture * tFixA = contact->GetFixtureA();
	b2Fixture * tFixB = contact->GetFixtureB();

	b2Node * tb2NodeA = nullptr;
	b2Node * tb2NodeB = nullptr;

	if (tFixA->GetBody()->GetUserData() != nullptr)
	{
		tb2NodeA = (b2Node *)tFixA->GetBody()->GetUserData();
	}
	if (tFixB->GetBody()->GetUserData() != nullptr)
	{
		tb2NodeB = (b2Node *)tFixB->GetBody()->GetUserData();
	}

	/*if (tb2NodeA != nullptr && tb2NodeB != nullptr)
	{
		callback(tb2NodeA, tFixB, tb2NodeB);
		callback(tb2NodeB, tFixA, tb2NodeA);
	}*/

	if (tb2NodeA != nullptr)
	{
		if ((tb2NodeB != nullptr) || tb2NodeA->IsWorldBoxCollision())
		{
			b2CollisionData data;
			data.other = tFixB;
			data.otherNode = tb2NodeB;

			if (tb2NodeA->IsWorldBoxCollision())
			{
				auto tTag = (b2WorldBoxData *)tFixB->GetUserData();
				data.worldBoxTag = tTag != nullptr ? tTag->GetTag() : WorldBoxTag::TAG_NONE;
			}
			callback(tb2NodeA, &data);
		}
	
	}
	if (tb2NodeB != nullptr)
	{
		if ((tb2NodeA != nullptr) ||(tb2NodeB->IsWorldBoxCollision() && ((b2WorldBoxData *)tFixA->GetUserData()) != nullptr))
		{
			b2CollisionData data;
			data.other = tFixA;
			data.otherNode = tb2NodeA;

			if (tb2NodeB->IsWorldBoxCollision())
			{
				auto tTag = (b2WorldBoxData *)tFixA->GetUserData();
				data.worldBoxTag = tTag != nullptr ? tTag->GetTag() : WorldBoxTag::TAG_NONE;
			}
			callback(tb2NodeB, &data);
		}
	
	}
}

void b2LayerContactListener::BeginContact(b2Contact * contact)
{
	OnNodeCallback(contact, [](b2Node * node, b2CollisionData * data)
	{
		node->OnCollisionEnter(data);
	});
}

void b2LayerContactListener::EndContact(b2Contact * contact)
{
	OnNodeCallback(contact, [](b2Node * node, b2CollisionData * data)
	{
		node->OnCollisionExit(data);
	});
}

void b2LayerContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	OnNodeCallback(contact, [](b2Node * node, b2CollisionData * data)
	{
		node->OnCollisionStay(data);
	});
}

void b2LayerContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}
