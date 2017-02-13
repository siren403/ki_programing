#pragma once

#include <stdio.h>

class Task;
class TaskList;

class TaskIter
{
private:
	TaskList * mpList = nullptr;
	Task * mpTask = nullptr;
public:
	TaskIter(TaskList * list);
	~TaskIter();


	bool HasNext();
	Task * Next();
	void Remove();
};

