#ifndef __MAPTILE_H__
#define __MAPTILE_H__

#include "Actor.h"
#include "IntUtils.h"
#include <functional>


class PlayMap;

class MapTile : public Actor
{

public:
	CREATE_FUNC(MapTile);
	virtual bool init() override;

	virtual void SetHighlight(bool isHighlight);

	void InitWithTileData(PlayMap * playMap,Vec2I tileIndex);
	Sprite * GetSprite();
	bool IsCollisionTile();
protected:
	PlayMap * mpPlayMap = nullptr;
	Sprite * mTileSprite = nullptr;
	Vec2I mTileIndex;

};


#endif // !__MAPTILE_H__
