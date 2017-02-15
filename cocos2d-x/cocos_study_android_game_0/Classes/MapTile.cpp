#include "MapTile.h"
#include "PlayMap.h"

bool MapTile::init()
{
	if (!Actor::init())
	{
		return false;
	}

	mType = ActorType::Actor_Tile;
	return true;
}

void MapTile::InitWithTileData(PlayMap * playMap, Vec2I tileIndex)
{
	mpPlayMap = playMap;
	mTileIndex = tileIndex;
	auto tileData = mpPlayMap->GetTileData(mTileIndex);
	mTileSprite = Sprite::create(tileData.fileName);
	this->addChild(mTileSprite, 0);
}

Sprite * MapTile::GetSprite()
{
	return mTileSprite;
}

bool MapTile::IsCollisionTile()
{
	return mpPlayMap->GetTileData(mTileIndex).isCollision;
}
