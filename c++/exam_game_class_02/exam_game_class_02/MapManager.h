#pragma once

#include "Player.h"
#include "defines.h"

class CMapManager
{
private:
	int mMap[MAP_LENGTH] = { 0 };//지정한 맵길이로 요소들 초기화
public:
	CMapManager();
	~CMapManager();

	void DrawMap();
	int* GetMap();
	char CheckSlimeEncount(CPlayer *tPlayer);
};

