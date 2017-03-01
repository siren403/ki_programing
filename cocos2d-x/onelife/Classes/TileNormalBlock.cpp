#include "TileNormalBlock.h"

bool TileNormalBlock::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_normal_wall.png");
	this->addChild(mTileSprite, 0);

	return true;
}
