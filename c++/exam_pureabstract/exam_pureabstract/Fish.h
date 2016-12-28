#pragma once
#include "Food.h"
class Fish :
	public Food
{
public:
	Fish();
	~Fish();

	void Print(int n) override;
};

