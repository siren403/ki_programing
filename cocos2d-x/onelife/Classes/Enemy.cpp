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

void Enemy::OnActivate(bool isActive)
{

}

void Enemy::AddState(int key, EnemyFiniteState * state)
{
	mFiniteState.insert(EnemyFSMap::value_type(key, state));
}
void Enemy::ChangeState(int key)
{
	float r = random(0.0f, 1.0f);

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
EnemyFiniteState * Enemy::GetState(int state)
{
	EnemyFSMap::iterator itor = mFiniteState.find(state);

	if (itor != mFiniteState.end())
	{
		return itor->second;
	}

	log("[%d] state is nullptr");

	return nullptr;
}



void Enemy::AddParts(int key, EnemyParts * tParts, bool isLifeParts, int localZOrder)
{
	mParts.insert(key, tParts);
	this->addChild(tParts, localZOrder);
	if (isLifeParts)
	{
		mLifeParts = tParts;
	}
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

EnemyPartsMap * Enemy::GetPartsMap()
{
	return &mParts;
}

void Enemy::SetAlive(bool tIsAlive)
{
	/*for (mPartMapItor = mParts.begin(); mPartMapItor != mParts.end(); ++mPartMapItor)
	{
		mPartMapItor->second->SetAlive(tIsAlive);
	}*/
	if (mLifeParts != nullptr)
	{
		mLifeParts->SetAlive(tIsAlive);
	}
}

bool Enemy::IsAlive()
{
	/*for (mPartMapItor = mParts.begin(); mPartMapItor != mParts.end(); ++mPartMapItor)
	{
		if (mPartMapItor->second->IsAlive())
		{
			return true;
		}
	}*/
	if (mLifeParts != nullptr)
	{
		return mLifeParts->IsAlive();
	}
	return false;
}

void Enemy::SetCameraFollow(bool isFollow)
{
	mIsFollow = isFollow;
}

bool Enemy::IsCameraFollow()
{
	return mIsFollow;
}

unsigned int Enemy::GetDeathCount()
{
	return mDeathCount;
}

// 0 ~ 1
void Enemy::SetOpacity(float value)
{
	for (mPartMapItor = mParts.begin(); mPartMapItor != mParts.end(); ++mPartMapItor)
	{
		mPartMapItor->second->GetSprite()->setOpacity(255 * value);
	}
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

	for (mPartMapItor = mParts.begin(); mPartMapItor != mParts.end(); ++mPartMapItor)
	{
		partsRect = utils::getCascadeBoundingBox(mPartMapItor->second);
		if (actorRect.intersectsRect(partsRect))
		{
			isCollision = true;
			other = mPartMapItor->second;

			if (actor->GetActorType() == ActorType::Actor_Arrow
				&& ((Arrow*)actor)->GetState() == Arrow::State::State_Shot
				&& mLifeParts == mPartMapItor->second)
			{
				mLifeParts->SetAlive(false);
				mDeathCount++;
			}
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
