#include "PlayMap.h"
#include "Actor.h"
#include "MapTile.h"

bool PlayMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	mCurrentMapData = DataManager::GetInstance()->GetMapData(mCurrentMapIndex);

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
	//auto mapData = mParseMapData[mCurrentMapIndex];
	return mCurrentMapData->tileDatas.at(mCurrentMapData->tilePlacement[tileIndex.y][tileIndex.x]);
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
	tileIndx.x = IntUtils::ClampI(tileIndx.x, 0, mCurrentMapWidth - 1);
	tileIndx.y = IntUtils::ClampI(tileIndx.y, 0, mCurrentMapHeight - 1);

	return tileIndx;
}

int PlayMap::GetTilePlacementData(Vec2I tileIndex)
{
	return mCurrentMapData->tilePlacement[tileIndex.y][tileIndex.x];
}

void PlayMap::CreateTiles(int mapIndex)
{
	mCurrentMapIndex = mapIndex;
	RemoveTiles();

	mCurrentMapData = DataManager::GetInstance()->GetMapData(mapIndex);
	if (mCurrentMapData == nullptr)
	{
		return;
	}
	//auto curMapData = mParseMapData.at(mCurrentMapIndex);

	mCurrentTiles.reserve(mCurrentMapData->tilePlacement.size());
	for (int y = 0; y < mCurrentMapData->tilePlacement.size(); y++)
	{
		MapTileVector * cols = new MapTileVector(mCurrentMapData->tilePlacement.at(y).size());
		for (int x = 0; x < mCurrentMapData->tilePlacement.at(y).size(); x++)
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
	
	mCurrentMapWidth = mCurrentMapData->tilePlacement.at(0).size();
	mCurrentMapHeight = mCurrentMapData->tilePlacement.size();
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
		Vec2I deltaTileIndex = Vec2I(IntUtils::ClampI(tileIndex.x + dir.x, 0, mCurrentMapWidth - 1), tileIndex.y);
		MapTile * tile = this->GetTile(deltaTileIndex);
		int tileType = mCurrentMapData->tilePlacement[deltaTileIndex.y][deltaTileIndex.x];

		if (mCurrentMapData->tileDatas.at(tileType).isCollision &&
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
		Vec2I deltaTileIndex = Vec2I(tileIndex.x, IntUtils::ClampI(tileIndex.y + dir.y, 0, mCurrentMapHeight - 1));
		int tileType = mCurrentMapData->tilePlacement[deltaTileIndex.y][deltaTileIndex.x];

		MapTile * tile = this->GetTile(deltaTileIndex);
		if (mCurrentMapData->tileDatas.at(tileType).isCollision &&
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


