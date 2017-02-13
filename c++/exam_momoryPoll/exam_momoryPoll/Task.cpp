#include "stdafx.h"
#include "Task.h"
#include "TaskList.h"

Task::Task(TaskList * list)
{
	mpPrev = list->mpActiveTask->mpPrev;
	mpNext = list->mpActiveTask;

	mpPrev->mpNext = mpNext->mpPrev = this;
}


Task::~Task()
{
	mpPrev->mpNext = mpNext;
	mpNext->mpPrev = mpPrev;
}
