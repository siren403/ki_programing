#include "ContectListener.h"

//상속받은 리스너를 생성하여 월드에 넘겨주면
//충돌 시 상황에 맞는 메소드가 호출됨
//현재 작성한 리스너는 충돌 발생 시 충돌 객체들을 SContacts로 묶어 vector에 담고
//충돌이 끝났을때에는 vector에서 찾아 erase시킨다.
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
