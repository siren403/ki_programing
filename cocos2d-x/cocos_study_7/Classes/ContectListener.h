#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

using namespace cocos2d;

struct SContacts
{
	b2Fixture * fixtureA;
	b2Fixture * fixtureB;

	bool operator == (const SContacts& other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class ContactListener : public b2ContactListener
{
public:
	std::vector<SContacts> mSContacts;

	ContactListener();
	~ContactListener();
	
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // !__CONTACTLISTENER_H__
