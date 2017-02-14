#ifndef __PLAYMAP_H__
#define __PLAYMAP_H__

#include "cocos2d.h"
#include "MapTileVector.h"
#include "IntUtils.h"
#include "DataManager.h"

using namespace cocos2d;

class Actor;

//struct TileData
//{
//	string fileName;
//	bool isCollision;
//};
//
//struct MapData
//{
//	map<int, TileData> tileDatas;
//	vector<vector<int>> tilePlacement;
//};

class PlayMap : public Node
{
private:

	//vector<MapData> mParseMapData;
	int mCurrentMapIndex = 0;
	MapData * mCurrentMapData = nullptr;

	int mTileWidth = 0;
	int mCurrentMapWidth = 0;
	int mCurrentMapHeight = 0;
	Vector<MapTileVector *> mCurrentTiles;

public:
	CREATE_FUNC(PlayMap);
	virtual bool init() override;

	float GetTileWidth();
	Size GetMapContentSize();
	MapTile * GetTile(Vec2 pos);
	TileData const GetTileData(Vec2I tileIndex);

	//temp
	int GetTilePlacementData(Vec2I tileIndex);
	MapTile * GetTile(Vec2 pos, Vec2I & outTileIndex);
	MapTile * GetTile(Vec2I tileIndex);
	Vec2I GetTileIndex(Vec2 pos);


	void CreateTiles(int mapIndex);
	void RemoveTiles();
	void CheckCollisionTile(Actor * actor, Vec2 dir);
};


#endif // !__PLAYMAP_H__
