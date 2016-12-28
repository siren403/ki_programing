#pragma once
#include "Food.h"
class Snack : public Food
{
public:
	Snack();
	~Snack();

	void SetPrice2();
	void PrintOverride(int t);
};

