#include "DataManager.h"
#include "cocos2d.h"
#include "json\document.h"
#include "json\reader.h"

#include <algorithm>

using namespace rapidjson;
using namespace cocos2d;

DataManager * DataManager::mInstance = nullptr;

DataManager * DataManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new DataManager();
	}
	return mInstance;
}

MapData * DataManager::GetMapData(int index)
{
	if (index >= 0 && index < mPlayMapData.size())
	{
		return &mPlayMapData[index];
	}
	return nullptr;
}

StageData * DataManager::GetStageData(int key)
{
	auto itor = mStageData.find(key);
	if (itor != mStageData.end())
	{
		return &itor->second;
	}
	return nullptr;
}

vector<string>* DataManager::GetTitleScripts()
{
	return &mTitleScripts;
}

void DataManager::SetMapSize(Size size)
{
	mCurrentMapSize = size;
}

Size DataManager::GetMapSize()
{
	return mCurrentMapSize;
}


DataManager::DataManager()
{
	string tJsonData;
	Document doc;

#pragma region Load PlayMap Data

	tJsonData = FileUtils::getInstance()->
		getStringFromFile("data/playmap.json");
	//log("read file data : %s", tJsonData.c_str());

	if (doc.Parse<0>(tJsonData.c_str()).HasParseError())
	{
		log("playmap.json parse error : %s", doc.GetParseError());
		return;
	}

	rapidjson::Value & docMaps = doc["maps"];
	//log("map count %d", docMaps.Size());
	for (int mapIndex = 0; mapIndex < docMaps.Size(); mapIndex++)
	{
		rapidjson::Value & docMapData = docMaps[mapIndex];
		MapData curMapData;

		//tileDatas
		rapidjson::Value & docTileDatas = docMapData["tileDatas"];
		for (int i = 0; i < docTileDatas.Size(); i++)
		{
			int key = docTileDatas[i]["key"].GetInt();

			rapidjson::Value & docTileData = docTileDatas[i]["data"];
			TileData curTileData;
			curTileData.tileName = docTileData["tileName"].GetString();
			curTileData.isCollision = docTileData["isCollision"].GetBool();

			curMapData.tileDatas.insert(pair<int, TileData>(key, curTileData));
		}

		//tilePlace
		rapidjson::Value & docTilePlacement = docMapData["tilePlacement"];
		curMapData.tilePlacement.reserve(docTilePlacement.Size());
		for (int y = 0; y < docTilePlacement.Size(); y++)
		{
			vector<int> cols;
			cols.reserve(docTilePlacement[y].Size());
			for (int x = 0; x < docTilePlacement[y].Size(); x++)
			{
				cols.push_back(docTilePlacement[y][x].GetInt());
			}
			curMapData.tilePlacement.push_back(cols);
		}
		reverse(curMapData.tilePlacement.begin(), curMapData.tilePlacement.end());

		curMapData.isLastMap = docMapData["isLastMap"].GetBool();

		mPlayMapData.push_back(curMapData);
	}
#pragma endregion

#pragma region Load Stage Data

	tJsonData = FileUtils::getInstance()->
		getStringFromFile("data/stage.json");
	//log("read file data : %s", tJsonData.c_str());

	if (doc.Parse<0>(tJsonData.c_str()).HasParseError())
	{
		log("stage.json parse error : %s", doc.GetParseError());
		return;
	}

	rapidjson::Value & docStages = doc["stages"];
	for (int stageIndex = 0; stageIndex < docStages.Size(); stageIndex++)
	{
		rapidjson::Value & docStageData = docStages[stageIndex];
		StageData curStageData;

		rapidjson::Value & docEnemyData = docStageData["enemy"];
		EnemyData curEnemyData;
		curEnemyData.id = docEnemyData["id"].GetInt();
		Vec2 pos = Vec2(docEnemyData["position"]["x"].GetFloat(),
			docEnemyData["position"]["y"].GetFloat());
		curEnemyData.position = pos;
		curEnemyData.cameraFollow = docEnemyData["cameraFollow"].GetBool();

		curStageData.enemy = curEnemyData;
		
		mStageData.insert(pair<int, StageData>(docStageData["key"].GetInt(),curStageData));
	}
#pragma endregion

	tJsonData = FileUtils::getInstance()->
		getStringFromFile("data/title_script.json");
	if (doc.Parse<0>(tJsonData.c_str()).HasParseError())
	{
		log("stage.json parse error : %s", doc.GetParseError());
		return;
	}
	rapidjson::Value & docScripts = doc["scripts"];
	for (int i = 0; i < docScripts.Size(); i++)
	{
		mTitleScripts.push_back(docScripts[i].GetString());
	}

	doc.RemoveAllMembers();
}


DataManager::~DataManager()
{
}

