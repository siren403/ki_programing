#pragma once

#include <iostream>
#include <stdio.h>

class TaskList;
class TaskIter;

class Task
{
	friend TaskList;
	friend TaskIter;

private:
	Task * mpPrev = nullptr;
	Task * mpNext = nullptr;
//test
public:
	void * operator new(size_t n)
	{
		std::cout << "operator new" << std::endl;
		return nullptr;
	}

	void operator delete(void * p)
	{

	}
public:
	Task(TaskList * list);
	virtual ~Task();
};

