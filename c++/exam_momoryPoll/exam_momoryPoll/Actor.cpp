#include "stdafx.h"
#include "Actor.h"
#include "TaskList.h"

#include "PoolManager.h"




Actor::Actor(TaskList * tpList) 
	: Unit(tpList)
{
}

Actor::~Actor()
{
}
void * Actor::operator new(size_t n)
{
	std::cout << "CActor::operator new" << std::endl;
	return PoolManager::GetInstance()->mpTaskActorList->New(n);
}

void Actor::operator delete(void * p)
{
	std::cout << "CActor::operator delete" << std::endl;
	PoolManager::GetInstance()->mpTaskActorList->Delete(p);
}