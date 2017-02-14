#include "Enemy.h"
#include "Arrow.h"
#include "EnemyFiniteState.h"

bool Enemy::init()
{
	if (!Actor::init())
	{
		return false;
	}

	this->scheduleUpdate();
	return true;
}

void Enemy::update(float dt)
{
	if (mCurrentFiniteState != nullptr)
	{
		mCurrentFiniteState->OnUpdate(dt);
	}
}

void Enemy::AddState(int key, EnemyFiniteState * state)
{
	mFiniteState.insert(EnemyFSMap::value_type(key, state));
}
void Enemy::ChangeState(int key)
{
	if (mIsScheduleUpdate == false)
	{
		this->scheduleUpdate();
		mIsScheduleUpdate = true;
	}
	auto state = mFiniteState.find(key);

	if (state != mFiniteState.end() && mCurrentFiniteState == (*state).second)
	{
		log("not change state : state to equals %d", key);
		return;
	}

	if (mCurrentFiniteState != nullptr)
	{
		mCurrentFiniteState->OnExit();
	}

	if (state != mFiniteState.end())
	{
		mCurrentFiniteState = (*state).second;
		mCurrentFiniteState->OnEnter();
	}

}

void Enemy::AddParts(int key, EnemyParts * tParts, int localZOrder)
{
	mParts.insert(key, tParts);
	this->addChild(tParts, localZOrder);
}

EnemyParts * Enemy::GetParts(int key)
{
	auto parts = mParts.find(key);
	if (parts != mParts.end())
	{
		return parts->second;
	}
	return nullptr;
}

void Enemy::SetAlive(bool tIsAlive)
{
	for (mMapPartItor = mParts.begin(); mMapPartItor != mParts.end(); ++mMapPartItor)
	{
		mMapPartItor->second->SetAlive(tIsAlive);
	}
}

bool Enemy::IsAlive()
{
	for (mMapPartItor = mParts.begin(); mMapPartItor != mParts.end(); ++mMapPartItor)
	{
		if (mMapPartItor->second->IsAlive())
		{
			return true;
		}
	}
	return false;
}

void Enemy::DestroyParts()
{
	//mDestroyPartsCount++;
	//log("%d", mDestroyPartsCount);

	//if (mDestroyPartsCount == 2)
	//{
	//	mParts.at(mParts.size() - 1)->setState(EnemyParts::STATE_ATTACK);
	//}
	//if (mDestroyPartsCount == 3)
	//{
	//	mParts.at(mParts.size() - 2)->setState(EnemyParts::STATE_ATTACK);
	//}
}


void Enemy::CheckCollisionActor(Actor * actor)
{
	bool isCollision = false;
	Actor * other = nullptr;
	Rect actorRect = utils::getCascadeBoundingBox(actor);
	Rect partsRect;

	for (mMapPartItor = mParts.begin(); mMapPartItor != mParts.end(); ++mMapPartItor)
	{
		partsRect = utils::getCascadeBoundingBox(mMapPartItor->second);
		if (actorRect.intersectsRect(partsRect))
		{
			isCollision = true;
			other = mMapPartItor->second;
			break;
		}
	}
	
	actor->OnCollisionOther(isCollision, other);
}



Enemy::~Enemy()
{
	EnemyFSMap::iterator itor;
	for (itor = mFiniteState.begin(); itor != mFiniteState.end(); ++itor)
	{
		delete (*itor).second;
	}
	mFiniteState.clear();

	log("enemy destroy");
}
