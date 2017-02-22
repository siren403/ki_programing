#ifndef __TILEWHITEFLOOR_H__
#define __TILEWHITEFLOOR_H__

#include "MapTile.h"

class TileWhiteFloor : public MapTile
{
public:
	CREATE_FUNC(TileWhiteFloor);
	virtual bool init() override;
};


#endif
