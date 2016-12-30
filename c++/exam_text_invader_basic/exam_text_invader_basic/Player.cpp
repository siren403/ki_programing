#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::SetUp(int tWidth, int tHeight)
{
	CCharacter::SetUp(tWidth, tHeight);
	mX = tWidth / 2;
	mY = tHeight - 1;
}

void CPlayer::Display(char * tpPixel)
{
	*(tpPixel + mY*mWidth + mX) = 'A';
}

void CPlayer::MoveActorWithInput(char tKey)
{
	switch (tKey)
	{
		//аб
	case 'Z':
	case 'z':
	{
		if (mX > 0)
		{
			mX = mX - 1;
		}
	}
	break;
	//©Л
	case 'X':
	case 'x':
	{
		if (mX < mWidth - 1)
		{
			mX = mX + 1;
		}
	}
	break;
	}
}
