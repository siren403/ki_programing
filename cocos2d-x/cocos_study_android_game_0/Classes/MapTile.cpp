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

void MapTile::SetHighlight(bool isHighlight)
{
}

void MapTile::InitWithTileData(PlayMap * playMap, Vec2I tileIndex)
{
	mpPlayMap = playMap;
	mTileIndex = tileIndex;
}

Sprite * MapTile::GetSprite()
{
	return mTileSprite;
}

bool MapTile::IsCollisionTile()
{
	return mpPlayMap->GetTileData(mTileIndex).isCollision;
}
