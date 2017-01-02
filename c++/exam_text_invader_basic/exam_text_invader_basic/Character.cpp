#include "stdafx.h"
#include "Character.h"
#include "gamesettings.h"
#include <math.h>
CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

void CCharacter::SetUp(int tX, int tY)
{
	mX = tX;
	mY = tY;
}

void CCharacter::Update()
{
}

void CCharacter::Clean(char * tpPixel)
{
	*(tpPixel + mY*WIDTH + mX) = 0;
}

int CCharacter::GetX()
{
	return mX;
}

void CCharacter::SetX(int tX)
{
	mX = tX;
}

int CCharacter::GetY()
{
	return mY;
}

void CCharacter::SetY(int tY)
{
	mY = tY;
}


