#pragma once

#include <stdio.h>

#include "TaskList.h"

class PoolManager
{
private:
	static PoolManager *mpInstance;

public:
	PoolManager();
	~PoolManager();

	static PoolManager *GetInstance();

	void CreateRyu();
	void DestroyRyu();

	void DisplayAllTaskList();


	//필요한 리스트들을 추가한다.

	//CEnemy용 고정크기영역 리스트
	//static CTaskList *mpTaskEnemyList;
	//CActor용 고정크기영역 리스트
	//static CTaskList *mpTaskActorList;


	//CEnemy용 고정크기영역 리스트
	TaskList *mpTaskEnemyList;
	//CActor용 고정크기영역 리스트
	TaskList *mpTaskActorList;
};

