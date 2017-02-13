#pragma once

#include <stdio.h>

class Task;
class TaskIter;

class TaskList
{

	friend Task;
	friend TaskIter;

private:
	char * mpBuffer = nullptr;
	Task * mpActiveTask = nullptr;
	Task * mpFreeTask = nullptr;

	size_t mTaskSize;
	size_t mTaskCount;

	Task * GetTask(size_t i);
public:
	TaskList(size_t size,size_t count);
	~TaskList();

	void * New(size_t size);
	void Delete(void * p);

	void DisplayActiveTaskList();
	void DisplayFreeTaskList();
};

