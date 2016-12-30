#pragma once
#include "Character.h"
#include <vector>

using namespace std;

class CPlayer :
	public Character
{
private:
	int mPosition = 0;

public:
	CPlayer();
	~CPlayer();

	int GetPosition();
	void SetPosition(int tPosition);

	void DoMove(vector<int>& tMap, int tIndex);
};

