#include "stdafx.h"
#include "Actor.h"

#include <iostream>

using namespace std;

CActor::CActor()
{
}


CActor::~CActor()
{
}

void CActor::DoIdle()
{
	cout << "[Actor] Idle" << endl;
}

void CActor::DoAttack()
{
	cout << "[Actor] Attack" << endl;
}
