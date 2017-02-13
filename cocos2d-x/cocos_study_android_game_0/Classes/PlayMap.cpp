#include "PlayMap.h"
#include "json\document.h"
#include "json\reader.h"
#include <algorithm>

using namespace rapidjson;

bool PlayMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	string tJsonData = FileUtils::getInstance()->
		getStringFromFile("data/playmap.json");
	log("read file data : %s", tJsonData.c_str());

	Document doc;

	if (doc.Parse<0>(tJsonData.c_str()).HasParseError())
	{
		log("parse error : %s", doc.GetParseError());
		return true;
	}

	rapidjson::Value & docMaps = doc["maps"];
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
			curTileData.fileName = docTileData["fileName"].GetString();
			
			curMapData.tileDatas.insert(pair<int, TileData>(key, curTileData));
		}

		//tilePlace
		rapidjson::Value & docTilePlacement = docMapData["tilePlacement"];
		for (int y = 0; y < docTilePlacement.Size(); y++)
		{
			vector<int> cols;
			for (int x = 0; x < docTilePlacement[y].Size(); x++)
			{
				cols.push_back(docTilePlacement[y][x].GetInt());
			}
			curMapData.tilePlacement.push_back(cols);
		}
		reverse(curMapData.tilePlacement.begin(), curMapData.tilePlacement.end());
		mParseData.push_back(curMapData);
	}

	doc.RemoveAllMembers();

	log("%s", mParseData.at(0).tileDatas.at(3).fileName.c_str());

	auto curMapData = mParseData.at(mCurParseDataIndex);

	for (int y = 0; y < curMapData.tilePlacement.size(); y++)
	{
		for (int x = 0; x < curMapData.tilePlacement.at(y).size(); x++)
		{
			auto sprTile = Sprite::create(curMapData.tileDatas[curMapData.tilePlacement.at(y).at(x)].fileName);
			if (mTileWidth == 0)
			{
				mTileWidth = sprTile->getContentSize().width;
			}

			Vec2 pos;
			pos.x = (mTileWidth*0.5) + mTileWidth * x;
			pos.y = (mTileWidth*0.5) + mTileWidth * y;
			sprTile->setPosition(pos);
			this->addChild(sprTile, 0);
		}
	}

	return true;
}

float PlayMap::GetTileWidth()
{
	return mTileWidth;
}
