#include "stdafx.h"
#include "TaskList.h"
#include "Task.h"


TaskList::TaskList(size_t size, size_t count)
	: mTaskSize(size),mTaskCount(count)
{
	//고정크기 영역을 테스크 갯수+2 만큼 확보
	mpBuffer = new char[mTaskSize*(mTaskCount + 2)];

	mpActiveTask = GetTask(0);
	mpActiveTask->mpPrev = mpActiveTask->mpNext = mpActiveTask;

	mpFreeTask = GetTask(1);
	for (size_t ti = 1; ti < mTaskCount + 2; ti++)
	{
		GetTask(ti)->mpPrev = nullptr;
		GetTask(ti)->mpNext = GetTask(ti + 1);
	}
	GetTask(mTaskCount + 1)->mpNext = mpFreeTask;
}

TaskList::~TaskList()
{
	delete[] mpBuffer;
}
Task * TaskList::GetTask(size_t i)
{
	return (Task*)(mpBuffer + mTaskSize * i);
}


void * TaskList::New(size_t size)
{
	if (mpFreeTask->mpNext == mpFreeTask)
	{
		return nullptr;
	}

	Task * task = mpFreeTask->mpNext;
	mpFreeTask->mpNext = task->mpNext;

	return task;
}

void TaskList::Delete(void * p)
{
	Task * task = (Task*)p;
	task->mpPrev = nullptr;
	task->mpNext = mpFreeTask->mpNext;

	mpFreeTask->mpNext = task;
}

void TaskList::DisplayActiveTaskList()
{
	std::cout << "---------------------------" << std::endl;

	Task *tpTemp = NULL;

	tpTemp = mpActiveTask;

	std::cout << "CTaskList::DisplayActiveTaskList" << std::endl;

	while (tpTemp->mpNext != this->mpActiveTask)
	{
		tpTemp = tpTemp->mpNext;

		std::cout << tpTemp << std::endl;
	}

	std::cout << "---------------------------" << std::endl;
}

void TaskList::DisplayFreeTaskList()
{
	std::cout << "---------------------------" << std::endl;

	Task *tpTemp = NULL;

	tpTemp = mpFreeTask;

	std::cout << "CTaskList::DisplayFreeTaskList" << std::endl;

	while (tpTemp->mpNext != this->mpFreeTask)
	{
		tpTemp = tpTemp->mpNext;

		std::cout << tpTemp << std::endl;
	}

	std::cout << "---------------------------" << std::endl;
}
