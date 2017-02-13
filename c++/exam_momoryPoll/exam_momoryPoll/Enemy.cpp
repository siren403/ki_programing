#include "stdafx.h"
#include "Enemy.h"
#include "TaskList.h"
#include "PoolManager.h"


Enemy::Enemy(TaskList * tpList)
	: Unit(tpList)
{
}

Enemy::~Enemy()
{
}

void * Enemy::operator new(size_t n)
{
	std::cout << "CEnemy::operator new" << std::endl;
	return PoolManager::GetInstance()->mpTaskEnemyList->New(n);
}

void Enemy::operator delete(void * p)
{
	std::cout << "CEnemy::operator delete" << std::endl;
	PoolManager::GetInstance()->mpTaskEnemyList->Delete(p);
}