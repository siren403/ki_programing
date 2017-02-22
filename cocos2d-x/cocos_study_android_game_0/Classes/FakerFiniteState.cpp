#include "FakerFiniteState.h"
#include "FakerParts.h"
#include "Faker.h"
#include "StopWatch.h"
#include "DataManager.h"

#define ALLSIDE_MAX_HEIGHT_RATIO 0.8
#define ALLSIDE_MIN_HEIGHT_RATIO 0.2
#define ALLSIDE_LEFT_MIN -0.3
#define ALLSIDE_LEFT_MAX -0.2
#define ALLSIDE_RIGHT_MIN 1.2
#define ALLSIDE_RIGHT_MAX 1.3
#define ALLSIDE_SPEED_MIN 200
#define ALLSIDE_SPEED_MAX 400

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
	lifeParts->SetMoveSpeed(200);

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
		if (random(0, 1) >= 0.5)
		{
			this->mEntity->ChangeState(Faker::State::State_AllSideShow);
		}
		else
		{
			this->mEntity->ChangeState(Faker::State::State_ShowLife);
		}
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
	
	auto mapSize = DataManager::GetInstance()->GetMapSize();
	Vec2 pos;
	for (int i = 0; i < lefts.size(); i++)
	{
		pos.x = random(mapSize.width * ALLSIDE_LEFT_MIN, mapSize.width * ALLSIDE_LEFT_MAX);
		pos.y = random(mapSize.height * ALLSIDE_MIN_HEIGHT_RATIO, mapSize.height * ALLSIDE_MAX_HEIGHT_RATIO);
		
		lefts.at(i)->SetOriginPosition(pos);
		lefts.at(i)->SetMoveDirection(0);
		lefts.at(i)->SetMoveSpeed(random(ALLSIDE_SPEED_MIN, ALLSIDE_SPEED_MAX));
		lefts.at(i)->SetState(FakerSheep::State::State_DirMove);
	}
	for (int i = 0; i < rights.size(); i++)
	{
		pos.x = random(mapSize.width * ALLSIDE_RIGHT_MIN, mapSize.width * ALLSIDE_RIGHT_MAX);
		pos.y = random(mapSize.height * ALLSIDE_MIN_HEIGHT_RATIO, mapSize.height * ALLSIDE_MAX_HEIGHT_RATIO);

		rights.at(i)->SetOriginPosition(pos);
		rights.at(i)->SetMoveDirection(180);
		rights.at(i)->SetMoveSpeed(random(ALLSIDE_SPEED_MIN, ALLSIDE_SPEED_MAX));
		rights.at(i)->SetState(FakerSheep::State::State_DirMove);
	}

	lefts.clear();
	rights.clear();
}

void FakerAllSideShow::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	if (mStopWatch->GetAccTime() > 8)
	{
		mEntity->ChangeState(Faker::State::State_AllHide);
	}
	//Vec2 pos = mEntity->GetPartsMap()->begin()->second->getPosition();
	//float alpha = ((FakerSheep*)mEntity->GetPartsMap()->begin()->second)->GetSprite()->getOpacity();
	//log("begin pos : %f,%f [%f]", pos.x, pos.y, alpha);
}

void FakerAllSideShow::OnExit()
{
	mStopWatch->OnReset();
}

#pragma endregion
