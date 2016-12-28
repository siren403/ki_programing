#pragma once
#include "Food.h"
class Fruit :
	public Food
{
public:
	Fruit();
	~Fruit();

	void Print(int n) override;
};

