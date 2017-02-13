#ifndef __PLAYMAP_H__
#define __PLAYMAP_H__

#include "cocos2d.h"
#include <map>
#include <vector>

using namespace cocos2d;
using namespace std;

struct TileData
{
	string fileName;
};

struct MapData
{
	map<int, TileData> tileDatas;
	vector<vector<int>> tilePlacement;
};

class PlayMap : public Node
{
private:
	int mTileWidth = 0;

	vector<MapData> mParseData;
	int mCurParseDataIndex = 0;
public:
	CREATE_FUNC(PlayMap);
	virtual bool init() override;

	float GetTileWidth();
};


#endif // !__PLAYMAP_H__
