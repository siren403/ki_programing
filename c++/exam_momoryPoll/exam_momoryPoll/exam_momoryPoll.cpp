// exam_momoryPoll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "TaskList.h"
#include "Enemy.h"
#include "Actor.h"
#include "PoolManager.h"

using namespace std;

int main()
{
	// insert code here...
	std::cout << "This is exam to manage memory!\n";



	cout << "size of CTask: " << sizeof(Task) << endl;
	cout << "size of CUnit: " << sizeof(Unit) << endl;
	cout << "size of CEnemy: " << sizeof(Enemy) << endl;
	cout << "size of CActor: " << sizeof(Actor) << endl;



	PoolManager::GetInstance()->CreateRyu();



	vector<Enemy *> tEnemyVec;

	Enemy *tpEnemy = NULL;


	//여기서 new는 C++에서 제공하는 원시적인 동적 메모리 할당을 사용하지 않고
	//고정영역크기 리스트를 이용한 메모리관리를 이용한다.
	tpEnemy = NULL;
	tpEnemy = new Enemy(PoolManager::GetInstance()->mpTaskEnemyList);
	tpEnemy->SetX(0);
	tpEnemy->SetY(0);

	tEnemyVec.push_back(tpEnemy);

	tpEnemy = NULL;
	tpEnemy = new Enemy(PoolManager::GetInstance()->mpTaskEnemyList);
	tpEnemy->SetX(100);
	tpEnemy->SetY(0);

	tEnemyVec.push_back(tpEnemy);


	Actor *tpActor = NULL;


	//여기서 new는 C++에서 제공하는 원시적인 동적 메모리 할당을 사용하지 않고
	//고정영역크기 리스트를 이용한 메모리관리를 이용한다.
	tpActor = NULL;
	tpActor = new Actor(PoolManager::GetInstance()->mpTaskActorList);
	tpActor->SetX(0);
	tpActor->SetY(0);

	//tActorVec.push_back(tpActor);




	int ti = 0;
	for (ti = 0; ti<tEnemyVec.size(); ti++)
	{
		cout << "X: " << tEnemyVec[ti]->GetX() << ", " << "Y: " << tEnemyVec[ti]->GetY() << endl;
	}

	PoolManager::GetInstance()->DisplayAllTaskList();










	if (NULL != tpActor)
	{
		delete tpActor;
		tpActor = NULL;
	}


	for (ti = 0; ti<tEnemyVec.size(); ti++)
	{
		//여기서 delete는 C++에서 제공하는 원시적인 동적 메모리 할당을 사용하지 않고
		//고정영역크기 리스트를 이용한 메모리관리를 이용한다.
		if (NULL != tEnemyVec[ti])
		{
			delete tEnemyVec[ti];
			tEnemyVec[ti] = NULL;
		}
	}
	tEnemyVec.clear();

	PoolManager::GetInstance()->DisplayAllTaskList();











	PoolManager::GetInstance()->DestroyRyu();
    return 0;
}

