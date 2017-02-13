#pragma once

#include <stdio.h>
#include "Unit.h"

class Enemy : public Unit
{
public:
	void* operator new(size_t n);
	void operator delete(void* p);

	//void *New(unsigned int tSize);
	//void Delete(void *tpPtr);

public:
	Enemy(TaskList* tpList);
	virtual ~Enemy();
};

