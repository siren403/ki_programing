#include "stdafx.h"
#include "Player.h"
#include "defines.h"

#include <iostream>


using namespace std;

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

int CPlayer::GetPosition()
{
	return mPosition;
}

void CPlayer::SetPosition(int tPosition)
{
	mPosition = tPosition;
}

void CPlayer::DoMove(int tMap[], int tIndex)
{
	if (tIndex >= 0 && tIndex < MAP_LENGTH)
	{
		tMap[mPosition] = 0;
		tMap[tIndex] = KIND_PLAYER;
		mPosition = tIndex;
	}
	else
	{
		int tInput = 0;

		printf("\t");
		printf("[ 이동 할 수 없다... ]");
		printf("\n");
		printf("Input Any Key");
		printf("\n");
		cin >> tInput;
	}
}
