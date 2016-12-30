#pragma once

#include "Player.h"
#include "defines.h"
#include <vector>

using namespace std;

class CMapManager
{
private:
	vector<int> mMap;
public:
	CMapManager();
	~CMapManager();

	void DrawMap();
	vector<int>& GetMap();
	char CheckSlimeEncount(CPlayer *tPlayer);
};

