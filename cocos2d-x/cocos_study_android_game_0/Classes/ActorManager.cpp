#include "ActorManager.h"
#include "Player.h"
#include "Boss.h"
#include "Juggler.h"
#include "Faker.h"

ActorManager * ActorManager::mInstance = nullptr;

ActorManager * ActorManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ActorManager();
	}
	return mInstance;
}

ActorManager::ActorManager()
{
	mEnemyCreateFunctions.insert(pair<int, EnemyCreateFunc>(1, []() 
	{
		return Boss::create();
	}));
	mEnemyCreateFunctions.insert(pair<int, EnemyCreateFunc>(2, []()
	{
		return Juggler::create();
	}));
	mEnemyCreateFunctions.insert(pair<int, EnemyCreateFunc>(3, []()
	{
		return Faker::create();
	}));
}

Player * ActorManager::GetPlayer()
{
	if (mPlayer == nullptr)
	{
		mPlayer = Player::create();
		mPlayer->retain();
	}
	return mPlayer;
}

Enemy * ActorManager::GetEnemy(int key)
{
	auto func = mEnemyCreateFunctions.find(key);

	if (func != mEnemyCreateFunctions.end())
	{
		return func->second();
	}
	return nullptr;
}

Vec2 ActorManager::ConvertPlayerToEntity(Node * entity)
{
	if (entity == nullptr)
	{
		log("ActorManager::ConvertPlayerToEntity : entity is nullptr");
		return Vec2::ZERO;
	}
	Vec2 pos = GetPlayer()->getParent()->convertToWorldSpace(GetPlayer()->getPosition());
	pos = entity->convertToNodeSpace(pos);
	return pos;
}

ActorManager::~ActorManager()
{
	CC_SAFE_RELEASE_NULL(mPlayer);
}
