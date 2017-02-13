#include "ActorManager.h"

ActorManager * ActorManager::mInstance = nullptr;

ActorManager::ActorManager()
{
}
ActorManager::~ActorManager()
{
}

ActorManager * ActorManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ActorManager();
	}
	return mInstance;
}

void ActorManager::SetPlayer(Player * player)
{
	mPlayer = player;
}

Player * ActorManager::GetPlayer()
{
	return mPlayer;
}
