#include "stdafx.h"
#include "Unit.h"
#include "config.h"
#include <math.h>
CUnit::CUnit()
{
}


CUnit::~CUnit()
{
}

void CUnit::SetUp(int tX, int tY)
{
	mX = tX;
	mY = tY;
}

void CUnit::Update()
{
}

void CUnit::Clean(char * tpPixel)
{
	*(tpPixel + mY*WIDTH + mX) = 0;
}

int CUnit::GetX()
{
	return mX;
}

void CUnit::SetX(int tX)
{
	mX = tX;
}

int CUnit::GetY()
{
	return mY;
}

void CUnit::SetY(int tY)
{
	mY = tY;
}

float CUnit::GetSpeedPower()
{
	return mSpeedPower;
}

void CUnit::SetSpeedPower(float tSpeedPower)
{
	mSpeedPower = tSpeedPower;
}

void CUnit::SetDisplayMark(char tMark)
{
	mDisplayMark = tMark;
}


void CUnit::SetAlive(bool tAlive)
{
	mIsAlive = tAlive;
}


bool CUnit::GetAlive()
{
	return mIsAlive;
}

