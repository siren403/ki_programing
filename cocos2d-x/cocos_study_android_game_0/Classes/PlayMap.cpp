#include "PlayMap.h"
#include "json\document.h"
#include "json\reader.h"
#include "Actor.h"
#include "MapTile.h"
#include <algorithm>

using namespace rapidjson;

bool PlayMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	
#pragma region Load Json Data


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

		mParseMapData.push_back(curMapData);
	}

	doc.RemoveAllMembers();

#pragma endregion

	//log("%s", mParseMapData.at(0).tileDatas.at(3).fileName.c_str());

	return true;
}

float PlayMap::GetTileWidth()
{
	return mTileWidth * this->getScale();
}

Size PlayMap::GetMapContentSize()
{
	Size size;

	size = Size((mTileWidth * mCurrentMapWidth)*this->getScale(),
		(mTileWidth * mCurrentMapHeight)*this->getScale());
	
	return size;
}

MapTile * PlayMap::GetTile(Vec2 pos)
{
	MapTile * tile = nullptr;
	Vec2I tileIndex = this->GetTileIndex(pos);
	//log("tileIndex %d,%d", tileIndex.x, tileIndex.y);
	tile = this->GetTile(tileIndex);
	return tile;
}

TileData const PlayMap::GetTileData(Vec2I tileIndex)
{
	auto mapData = mParseMapData[mCurrentMapIndex];
	return mapData.tileDatas.at(mapData.tilePlacement[tileIndex.y][tileIndex.x]);
}

MapTile * PlayMap::GetTile(Vec2 pos, Vec2I & outTileIndex)
{
	MapTile * tile = nullptr;
	Vec2I tileIndex = this->GetTileIndex(pos);
	outTileIndex = tileIndex;

	tile = this->GetTile(tileIndex);

	return tile;

}

MapTile * PlayMap::GetTile(Vec2I tileIndex)
{
	return mCurrentTiles.at(tileIndex.y)->At(tileIndex.x);
}

Vec2I PlayMap::GetTileIndex(Vec2 pos)
{
	Vec2I tileIndx;

	tileIndx.x = pos.x / this->GetTileWidth();
	tileIndx.y = pos.y / this->GetTileWidth();
	tileIndx.x = ClampI(tileIndx.x, 0, mCurrentMapWidth - 1);
	tileIndx.y = ClampI(tileIndx.y, 0, mCurrentMapHeight - 1);

	return tileIndx;
}

int PlayMap::GetTilePlacementData(Vec2I tileIndex)
{
	return mParseMapData[mCurrentMapIndex].tilePlacement[tileIndex.y][tileIndex.x];
}

void PlayMap::CreateTiles(int mapIndex)
{
	mCurrentMapIndex = mapIndex;
	RemoveTiles();

	auto curMapData = mParseMapData.at(mCurrentMapIndex);

	mCurrentTiles.reserve(curMapData.tilePlacement.size());
	for (int y = 0; y < curMapData.tilePlacement.size(); y++)
	{
		MapTileVector * cols = new MapTileVector(curMapData.tilePlacement.at(y).size());
		for (int x = 0; x < curMapData.tilePlacement.at(y).size(); x++)
		{
			//auto mapTile = Sprite::create(curMapData.tileDatas[curMapData.tilePlacement.at(y).at(x)].fileName);
			auto mapTile = MapTile::create();
			mapTile->InitWithTileData(this, Vec2I(x, y));

			if (mTileWidth == 0)
			{
				mTileWidth = mapTile->GetSprite()->getContentSize().width * this->getScale();
			}

			Vec2 pos;
			pos.x = (mTileWidth * 0.5) + mTileWidth * x;
			pos.y = (mTileWidth * 0.5) + mTileWidth * y;
			mapTile->setPosition(pos);
			this->addChild(mapTile, 0);
			
			cols->GetMapTiles().pushBack(mapTile);
		}
		mCurrentTiles.pushBack(cols);
	}
	
	mCurrentMapWidth = curMapData.tilePlacement.at(0).size();
	mCurrentMapHeight = curMapData.tilePlacement.size();
}


void PlayMap::RemoveTiles()
{
	if (mCurrentTiles.size() > 0)
	{
		for (int y = 0; y < mCurrentTiles.size(); y++)
		{
			for (int x = 0; x < mCurrentTiles.at(y)->GetMapTiles().size(); x++)
			{
				this->removeChild(mCurrentTiles.at(y)->At(x));
			}
			mCurrentTiles.at(y)->GetMapTiles().clear();
		}
		mCurrentTiles.clear();
	}
}

void PlayMap::CheckCollisionTile(Actor * actor, Vec2 dir)
{
	Vec2I tileIndex = this->GetTileIndex(actor->getPosition());

	dir.x = dir.x > 0 ? 1 : dir.x < 0 ? -1 : 0;
	dir.y = dir.y > 0 ? 1 : dir.y < 0 ? -1 : 0;


	if (dir.x != 0)
	{
		Vec2I deltaTileIndex = Vec2I(ClampI(tileIndex.x + dir.x, 0, mCurrentMapWidth - 1), tileIndex.y);
		MapTile * tile = this->GetTile(deltaTileIndex);
		int tileType = mParseMapData[mCurrentMapIndex].tilePlacement[deltaTileIndex.y][deltaTileIndex.x];

		if (mParseMapData[mCurrentMapIndex].tileDatas.at(tileType).isCollision &&
			utils::getCascadeBoundingBox(tile).intersectsRect(utils::getCascadeBoundingBox(actor)))
		{
			//	log("collision tile dx");
			actor->OnCollisionOther(true, tile);
		}
	}
	else
	{
		actor->OnCollisionOther(false, nullptr);
	}

	if (dir.y != 0)
	{
		Vec2I deltaTileIndex = Vec2I(tileIndex.x, ClampI(tileIndex.y + dir.y, 0, mCurrentMapHeight - 1));
		int tileType = mParseMapData[mCurrentMapIndex].tilePlacement[deltaTileIndex.y][deltaTileIndex.x];

		MapTile * tile = this->GetTile(deltaTileIndex);
		if (mParseMapData[mCurrentMapIndex].tileDatas.at(tileType).isCollision &&
			utils::getCascadeBoundingBox(tile).intersectsRect(utils::getCascadeBoundingBox(actor)))
		{
			actor->OnCollisionOther(true, tile);
		}
	}
	else
	{
		actor->OnCollisionOther(false, nullptr);
	}
}


int PlayMap::ClampI(int value, int min, int max)
{
	return value < min ? min : value>max ? max : value;
}