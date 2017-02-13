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
	auto tileData = mpPlayMap->GetTileData(tileIndex);
	mTileSprite = Sprite::create(tileData.fileName);
	this->addChild(mTileSprite, 0);
}

Sprite * MapTile::GetSprite()
{
	return mTileSprite;
}
