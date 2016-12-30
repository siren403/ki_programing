#include "stdafx.h"
#include "Character.h"


CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

void CCharacter::SetUp(int tWidth, int tHeight)
{
	mWidth = tWidth;
	mHeight = tHeight;
}

void CCharacter::Clean(char * tpPixel)
{
	*(tpPixel + mY*mWidth + mX) = 0;
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


