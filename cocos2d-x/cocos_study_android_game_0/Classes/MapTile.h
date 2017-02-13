#ifndef __MAPTILE_H__
#define __MAPTILE_H__

#include "Actor.h"
#include "IntUtils.h"

class PlayMap;

class MapTile : public Actor
{
private:
	PlayMap * mpPlayMap = nullptr;
	Sprite * mTileSprite = nullptr;

public:
	CREATE_FUNC(MapTile);
	virtual bool init() override;

	void InitWithTileData(PlayMap * playMap,Vec2I tileIndex);

	Sprite * GetSprite();
};

#endif // !__MAPTILE_H__
