#include "stdafx.h"
#include "TaskIter.h"

#include "TaskList.h"
#include "Task.h"


TaskIter::TaskIter(TaskList * list)
	: mpList(list),mpTask(list->mpActiveTask)
{
}

TaskIter::~TaskIter()
{
}

bool TaskIter::HasNext()
{
	return mpTask->mpNext != mpList->mpActiveTask;
}

Task * TaskIter::Next()
{
	return mpTask = mpTask->mpNext;
}

void TaskIter::Remove()
{
	mpTask = mpTask->mpPrev;
	delete mpTask->mpNext;
}
