#include "ContectListener.h"

ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact * contact)
{
	log("Begin Contact");
	SContacts tSContacts;
	tSContacts.fixtureA = contact->GetFixtureA();
	tSContacts.fixtureB = contact->GetFixtureB();

	mSContacts.push_back(tSContacts);
}

void ContactListener::EndContact(b2Contact * contact)
{
	log("EndContact");

	SContacts myContact = { contact->GetFixtureA(),contact->GetFixtureB() };
	std::vector<SContacts>::iterator pos;
	pos = std::find(mSContacts.begin(), mSContacts.end(), myContact);

	if (pos != mSContacts.end())
	{
		mSContacts.erase(pos);
	}
}

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}
