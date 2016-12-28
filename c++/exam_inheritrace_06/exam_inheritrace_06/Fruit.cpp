#include "stdafx.h"
#include "Fruit.h"


Fruit::Fruit()
{
}


Fruit::~Fruit()
{
}

void Fruit::Print(int n)
{
	Food::Print(n + 100);
}
