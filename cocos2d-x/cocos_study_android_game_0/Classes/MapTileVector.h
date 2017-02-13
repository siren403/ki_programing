#ifndef __SPRITEVECTOR_H__
#define __SPRITEVECTOR_H__

#include "cocos2d.h"

class MapTile;

using namespace cocos2d;

class MapTileVector : public Ref
{
private:
	Vector<MapTile *> mMapTiles;
public:
	MapTileVector();
	MapTileVector(int reserve);
	~MapTileVector();

	Vector<MapTile *> & GetMapTiles();
	MapTile * At(int index);
};

#endif // !__SPRITEVECTOR_H__
