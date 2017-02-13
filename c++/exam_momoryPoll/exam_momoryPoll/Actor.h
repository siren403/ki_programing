#pragma once

#include <stdio.h>

#include "Unit.h"

class Actor : public Unit
{
private:
	unsigned int mHP = 0;
	unsigned int mMP = 0;

public:
	void* operator new(size_t n);
	void operator delete(void* p);

public:
	Actor(TaskList* tpList);
	virtual ~Actor();

};

