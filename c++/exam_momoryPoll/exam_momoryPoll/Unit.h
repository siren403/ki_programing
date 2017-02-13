#pragma once

#include <stdio.h>

#include "Task.h"

class Unit : public Task
{
public:
	float mX = 0.0f;
	float mY = 0.0f;

	bool mIsAlive = false;


	Unit(TaskList* tpList);
	virtual ~Unit();


	float GetX() { return mX; };
	float GetY() { return mY; };

	void SetX(float tX) { mX = tX; };
	void SetY(float tY) { mY = tY; };
};

