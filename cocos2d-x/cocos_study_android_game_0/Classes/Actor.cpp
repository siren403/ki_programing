#include "Actor.h"

bool Actor::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

bool Actor::IsAlive()
{
	return mIsAlive;
}

void Actor::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}
