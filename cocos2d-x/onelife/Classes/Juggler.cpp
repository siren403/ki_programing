#include "Juggler.h"
#include "JugglerParts.h"
#include "JugglerFiniteState.h"
#include "ActorManager.h"
#include "PlayMap.h"
#include "MapTile.h"

#define PI 3.14159f

bool Juggler::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	mCircleCount = 12;
	mCircleRadius = 100;
	mCirclePivot = (PI * 2) * 0.75f;

	auto lifeParts = JugglerCircle::create();
	lifeParts->SetState(JugglerCircle::State::State_None);
	//lifeParts->GetSprite()->setColor(Color3B::RED);
	this->AddParts(LIFEPARTS_KEY, lifeParts, true);

	JugglerCircle * circle = nullptr;

	//Vec2 pos;
	for (int i = 0; i < mCircleCount; i++)
	{
		circle = JugglerCircle::create();
		circle->SetRotateData(CircleRotateData(i, mCircleCount, mCircleRadius, mCirclePivot));
		circle->StartAnimation();
		this->AddParts(i, circle);
		circle->GetSprite()->setColor(Color3B(200,200,200));
		if (i == 0)
		{
			//circle->GetSprite()->setColor(Color3B::GREEN);
		}
	}

	this->AddState(State::State_None, JugglerNoneState::Create(this));
	this->AddState(State::State_Idle, JugglerIdleState::Create(this));
	this->AddState(State::State_SeqAttack, JugglerSeqAttackState::Create(this));
	this->AddState(State::State_RushAttack, JugglerRushAttackState::Create(this));
	this->AddState(State::State_CornerAttack, JugglerCornerAttackState::Create(this));
	this->AddState(State::State_ColRowAttack, JugglerColRowAttack::Create(this));


	auto map = ActorManager::GetInstance()->GetPlayMap();
	vector<Vec2I> outlineTileIndex;
	for (int x = map->GetMapWidth() - 1; x >= 0; x--)
		outlineTileIndex.push_back(Vec2I(x, 0));
	for (int y = 0; y < map->GetMapHeight(); y++)
		outlineTileIndex.push_back(Vec2I(0, y));
	for (int x = 0; x < map->GetMapWidth(); x++)
		outlineTileIndex.push_back(Vec2I(x, map->GetMapHeight() - 1));
	for (int y = map->GetMapHeight() - 1; y >= 0; y--)
		outlineTileIndex.push_back(Vec2I(map->GetMapWidth() - 1, y));
	
	for (int i = 0; i < outlineTileIndex.size(); i++)
	{
		map->GetTile(outlineTileIndex[i])->SetHighlight(true, 0.15f * i);
	}

	mNextStates.push_back(Juggler::State::State_Idle);
	mNextStates.push_back(Juggler::State::State_RushAttack);
	mNextStates.push_back(Juggler::State::State_SeqAttack);
	mNextStates.push_back(Juggler::State::State_CornerAttack);
	mNextStates.push_back(Juggler::State::State_ColRowAttack);

	return true;
}


void Juggler::OnActivate(bool isActive)
{
	if (isActive)
	{

	}
	else
	{
		GetParts(LIFEPARTS_KEY)->setPosition(Vec2::ZERO);

		for (int i = 0; i < mCircleCount; i++)
		{
			((JugglerCircle*)GetParts(i))->Reposition();
		}
		this->ChangeState(State::State_Idle);

	}
	this->GetState(State::State_Idle)->SetActive(isActive);
	
}

int Juggler::GetCircleCount()
{
	return mCircleCount;
}

float Juggler::GetCircleRadius()
{
	return mCircleRadius;
}

float Juggler::GetCirclePivot()
{
	return mCirclePivot;
}

void Juggler::RandomChangeState()
{
	//NextState
	//int max = IntUtils::ClampI((int)(GetDeathCount() / 1), 0, mNextStates.size() - 1);
	int max = IntUtils::ClampI(GetDeathCount() + 1, 0, mNextStates.size() - 1);
	EnemyFiniteState * state = nullptr;
	int selectStateType = 0;
	do
	{
		selectStateType = mNextStates[random(0, max)];
		state = GetState(selectStateType);
	} while (state == mCurrentFiniteState);

	//max = 2;
	ChangeState(selectStateType);
}


