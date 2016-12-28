#include "stdafx.h"
#include "Actor.h"

#include <iostream>

using namespace std;

CActor::CActor()
{
}


CActor::~CActor()
{
	cout << "[ENd]ACtor" << endl;

}

void CActor::Doit()
{
	cout << "CActor" << endl;
}
