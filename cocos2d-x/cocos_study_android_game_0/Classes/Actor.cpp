#include "Actor.h"

bool Actor::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

bool Actor::GetIsAlive()
{
	return mIsAlive;
}

void Actor::SetIsAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}
