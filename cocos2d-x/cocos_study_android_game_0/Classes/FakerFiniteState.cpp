#include "FakerFiniteState.h"
#include "FakerParts.h"
#include "Faker.h"
#include "StopWatch.h"

#pragma region Idle

bool FakerIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	

	return true;
}

FakerIdleState::~FakerIdleState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void FakerIdleState::OnEnter()
{
}

void FakerIdleState::OnUpdate(float dt)
{
	if (mIsActive)
	{
		mStopWatch->OnUpdate(dt);
		if (mStopWatch->GetAccTime() >= 1)
		{
			mEntity->ChangeState(Faker::State::State_ShowLife);
			log("idle end");
		}
	}
}

void FakerIdleState::OnExit()
{
	mStopWatch->OnReset();
}
#pragma endregion


#pragma region ShowLife

bool FakerShowLifeState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	return true;
}

FakerShowLifeState::~FakerShowLifeState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void FakerShowLifeState::OnEnter()
{
	auto lifeParts = (FakerSheep*)this->GetEntity<Faker>()->GetParts(LIFEPARTS_KEY);
	
	Vec2 pos = Vec2(1200, 400);
	lifeParts->SetOriginPosition(pos);
	lifeParts->SetMoveDirection(130);
	//lifeParts->SetMoveDirection(180);
	lifeParts->SetMoveSpeedPower(200);

	lifeParts->SetState(FakerSheep::State::State_DirMove);
}

void FakerShowLifeState::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	if (mStopWatch->GetAccTime() >= 3)//6
	{
		mEntity->ChangeState(Faker::State::State_AllHide);
	}
}

void FakerShowLifeState::OnExit()
{
	mStopWatch->OnReset();
}

#pragma endregion

#pragma region AllHide

bool FakerAllHide::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	return true;
}

FakerAllHide::~FakerAllHide()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void FakerAllHide::OnEnter()
{
	EnemyPartsMap * partsMap = this->mEntity->GetPartsMap();
	EnemyPartsMap::iterator itor;
	for (itor = partsMap->begin(); itor != partsMap->end(); itor++)
	{
		((FakerSheep*)itor->second)->SetState(FakerSheep::State::State_Hide);
	}
	mSheepHideDuration = ((FakerSheep*)partsMap->begin()->second)->GetHideDuration();
}

void FakerAllHide::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);

	if (mStopWatch->GetAccTime() > mSheepHideDuration)
	{
		this->mEntity->ChangeState(Faker::State::State_AllSideShow);
	}
}

void FakerAllHide::OnExit()
{
	mStopWatch->OnReset();
}
#pragma endregion

#pragma region AllSideShow

bool FakerAllSideShow::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();


	return true;
}

FakerAllSideShow::~FakerAllSideShow()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void FakerAllSideShow::OnEnter()
{
	EnemyPartsMap * partsMap = mEntity->GetPartsMap();
	EnemyPartsMap::iterator itor;
	int maxCount = (partsMap->size() / 2) + 1;

	Vector<FakerSheep*> lefts;
	Vector<FakerSheep*> rights;

	for (itor = partsMap->begin(); itor != partsMap->end(); itor++)
	{
		bool isLeft = cocos2d::rand_0_1() > 0.5;

		isLeft = isLeft ? 
			lefts.size() >= maxCount ? false : true : 
			//else
			rights.size() >= maxCount ? true : false;

		if (isLeft)
		{
			lefts.pushBack((FakerSheep*)itor->second);
		}
		else
		{
			rights.pushBack((FakerSheep*)itor->second);
		}
	}

	Vec2 pos;
	for (int i = 0; i < lefts.size(); i++)
	{
		pos.x = 700;
		pos.y = 100;
		pos.y += 90 * i;
		lefts.at(i)->SetOriginPosition(pos);
	}
	for (int i = 0; i < rights.size(); i++)
	{
		pos.x = 800;
		pos.y = 100;
		pos.y += 90 * i;
		rights.at(i)->SetOriginPosition(pos);
	}

	lefts.clear();
	rights.clear();
}

void FakerAllSideShow::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
}

void FakerAllSideShow::OnExit()
{
	mStopWatch->OnReset();
}

#pragma endregion
