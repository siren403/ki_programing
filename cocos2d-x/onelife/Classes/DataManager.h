#pragma once

#include "cocos2d.h"

#include <map>
#include <vector>

using namespace std;
using namespace cocos2d;

#pragma region structs PlayMap

struct TileData
{
	string tileName;
	bool isCollision;
};

struct MapData
{
	map<int, TileData> tileDatas;
	vector<vector<int>> tilePlacement;
	bool isLastMap;
};

#pragma endregion

#pragma region structs Stage

struct EnemyData
{
	int id;
	Vec2 position;
	bool cameraFollow;
};

struct StageData
{
	EnemyData enemy;
};

#pragma endregion


class DataManager
{
private:
	static DataManager * mInstance;
	DataManager();
	~DataManager();
public:
	static DataManager * GetInstance();

private:
	vector<MapData> mPlayMapData;
	map<int, StageData> mStageData;
	vector<string> mTitleScripts;
	Size mCurrentMapSize;
public:
	MapData * GetMapData(int index);
	StageData * GetStageData(int key);
	vector<string> * GetTitleScripts();

	void SetMapSize(Size size);
	Size GetMapSize();
};