#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	if (mpActorSprite != nullptr)
	{
		this->removeChild(mpActorSprite);
		mpActorSprite = nullptr;
	}
}

Actor * Actor::create()
{
	Actor * tpActor = new Actor();
	if (tpActor->init())
	{
		tpActor->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(tpActor);
	}
	return tpActor;
}

Actor * Actor::create(int tHp)
{
	auto tpActor = Actor::create();
	if (tpActor != nullptr)
	{
		tpActor->mMaxHp = tHp;
		tpActor->mCurHp = tHp;
	}
	return tpActor;
}

bool Actor::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	return true;
}

void Actor::SetSprite(Sprite * tpSprite)
{
	if (mpActorSprite != nullptr)
	{
		this->removeChild(mpActorSprite);
		mpActorSprite = nullptr;
	}

	mpActorSprite = tpSprite;
	this->addChild(mpActorSprite);
}

Sprite * Actor::GetSprite()
{
	return mpActorSprite;
}

void Actor::initHp(int tHp)
{
	mMaxHp = tHp;
	mCurHp = tHp;
}
