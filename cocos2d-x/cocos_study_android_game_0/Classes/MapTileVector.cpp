#include "MapTileVector.h"
#include "MapTile.h"

MapTileVector::MapTileVector()
{
}

MapTileVector::MapTileVector(int reserve)
{
	mMapTiles.reserve(reserve);
}

MapTileVector::~MapTileVector()
{
}

Vector<MapTile*> & MapTileVector::GetMapTiles()
{
	return mMapTiles;
}

MapTile * MapTileVector::At(int index)
{
	return mMapTiles.at(index);
}
