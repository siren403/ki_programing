#include "TileWhiteFloor.h"

bool TileWhiteFloor::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_normal_floor.png");
	this->addChild(mTileSprite, 0);

	return true;
}
