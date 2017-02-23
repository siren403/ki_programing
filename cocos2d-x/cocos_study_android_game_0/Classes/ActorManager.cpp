#include "ActorManager.h"
#include "Player.h"
#include "Boss.h"
#include "Juggler.h"
#include "Faker.h"
#include "PlayMap.h"
#include "TileWhiteFloor.h"
#include "TileNormalBlock.h"
#include "TileBlackFloor.h"
#include "TileBlackBlock.h"

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
#pragma region CreataEnemyFunc

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
#pragma endregion

#pragma region CreateMapTile

	mMapTileCreateFunctions.insert(pair<string, MapTileCreateFunc>("white_floor", []() 
	{
		return TileWhiteFloor::create();
	}));
	mMapTileCreateFunctions.insert(pair<string, MapTileCreateFunc>("normal_block", []()
	{
		return TileNormalBlock::create();
	}));
	mMapTileCreateFunctions.insert(pair<string, MapTileCreateFunc>("black_floor", []()
	{
		return TileBlackFloor::create();
	}));
	mMapTileCreateFunctions.insert(pair<string, MapTileCreateFunc>("black_block", []()
	{
		return TileBlackBlock::create();
	}));
#pragma endregion


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

Enemy * ActorManager::CreateEnemy(int key)
{
	auto func = mEnemyCreateFunctions.find(key);

	if (func != mEnemyCreateFunctions.end())
	{
		return func->second();
	}
	return nullptr;
}

PlayMap * ActorManager::GetPlayMap()
{
	if (mPlayMap == nullptr)
	{
		mPlayMap = PlayMap::create();
	}
	return mPlayMap;
}

MapTile * ActorManager::CreateTile(string key)
{
	auto func = mMapTileCreateFunctions.find(key);

	if (func != mMapTileCreateFunctions.end())
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
