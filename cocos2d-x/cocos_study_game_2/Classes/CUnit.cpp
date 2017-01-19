#include "CUnit.h"

bool CUnit::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

bool CUnit::getIsAlive()
{
	return mIsAlive;
}

void CUnit::setIsAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}

bool CUnit::lateInit()
{
	return true;
}


