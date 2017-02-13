#include "stdafx.h"
#include "PoolManager.h"
#include "TaskIter.h"

#include <iostream>

using namespace std;

PoolManager *PoolManager::mpInstance = nullptr;

PoolManager::PoolManager()
{
}


PoolManager::~PoolManager()
{
}

PoolManager * PoolManager::GetInstance()
{
	if (nullptr == mpInstance)
	{
		mpInstance = new PoolManager();
		return mpInstance;
	}

	return mpInstance;
}

void PoolManager::CreateRyu()
{
	//CEnemy용으로 64바이트짜리 원소 5개를 가진 메모리 리스트를 미리 만들어둠.
	mpTaskEnemyList = new TaskList(64, 5);

	//CActor용으로 96바이트짜리 원소 2개를 가진 메모리 리스트를 미리 만들어둠.
	mpTaskActorList = new TaskList(96, 2);
}

void PoolManager::DestroyRyu()
{
	if (NULL != mpTaskActorList)
	{
		delete mpTaskActorList;
		mpTaskActorList = NULL;
	}

	if (NULL != mpTaskEnemyList)
	{
		delete mpTaskEnemyList;
		mpTaskEnemyList = NULL;
	}
}

void PoolManager::DisplayAllTaskList()
{
	std::cout << "      " << endl;
	cout << "CRyuMgr::DisplayAllTaskList" << endl;
	std::cout << "=========================" << std::endl;

	std::cout << "      Enemy: " << endl;

	for (TaskIter tItor(mpTaskEnemyList); tItor.HasNext();)
	{
		cout << "enemy list " << tItor.Next() << endl;
	}


	mpTaskEnemyList->DisplayActiveTaskList();
	mpTaskEnemyList->DisplayFreeTaskList();



	std::cout << "      Actor: " << endl;

	for (TaskIter tItor(mpTaskActorList); tItor.HasNext();)
	{
		cout << "actor list " << tItor.Next() << endl;
	}

	mpTaskActorList->DisplayActiveTaskList();
	mpTaskActorList->DisplayFreeTaskList();


	std::cout << "=========================" << std::endl;
}
