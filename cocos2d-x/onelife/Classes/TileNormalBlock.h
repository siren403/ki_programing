#ifndef __TILENORMALBLOCK_H__
#define __TILENORMALBLOCK_H__

#include "MapTile.h"

class TileNormalBlock : public MapTile
{
public:
	CREATE_FUNC(TileNormalBlock);
	virtual bool init() override;
};

#endif // !__TILENORMALBLOCK_H__
