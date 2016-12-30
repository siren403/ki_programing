#include "stdafx.h"
#include "MapManager.h"

CMapManager::CMapManager()
{
	mMap.reserve(MAP_LENGTH);

	int ti = 0;
	for (ti = 0; ti < mMap.capacity(); ti++)
	{
		mMap.push_back(0);
	}
}

CMapManager::~CMapManager()
{
}

void CMapManager::DrawMap()
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n");
	printf("==");
	for (ti = 0; ti < mMap.size(); ti++)
	{
		switch (mMap[ti])
		{
		case KIND_PLAYER:
			printf("[  PLAYER  ]==");
			break;
		case KIND_NORMAL_SLIME:
			printf("[  SLIME   ]==");
			break;
		case KIND_BOSS_SLIME:
			printf("[BOSS SLIME]==");
			break;
		case 0://¾øÀ½
		default:
			printf("[          ]==");
			break;
		}
	}
	printf("\n");
	printf("====================================");
	printf("====================================");
	printf("\n\n");
}

vector<int>& CMapManager::GetMap()
{
	return mMap;
}

char CMapManager::CheckSlimeEncount(CPlayer * tPlayer)
{
	char tResult = 0;

	if (tPlayer != NULL && tPlayer->GetPosition() < MAP_LENGTH - 1)
	{
		if (mMap[tPlayer->GetPosition() + 1] != 0)
		{
			tResult = 1;
		}
	}
	return tResult;
}
