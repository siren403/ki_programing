#pragma once
#include "Character.h"
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

	void DoMove(int tMap[], int tIndex);
};

