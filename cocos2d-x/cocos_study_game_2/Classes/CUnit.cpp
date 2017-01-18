#include "CUnit.h"

bool CUnit::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

bool CUnit::lateInit()
{
	return true;
}


