#include "JugglerFiniteState.h"
#include "Juggler.h"
#include "JugglerParts.h"
#include "StopWatch.h"
#include "ActorManager.h"
#include "Player.h"

#pragma region Idle

bool JugglerIdleState::InitState()
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

JugglerIdleState::~JugglerIdleState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerIdleState::OnEnter()
{
	auto circles = this->GetEntity<Juggler>();
	Vec2 pos;
	for (int i = 0; i < circles->GetCircleCount(); i++)
	{
		((JugglerCircle*)circles->GetPartsMap()->at(i))->SetState(JugglerCircle::State::State_Idle);
	}
}

void JugglerIdleState::OnUpdate(float dt)
{
	if (mIsActive)
	{
		auto player = ActorManager::GetInstance()->GetPlayer();
		Vec2 pos;
		pos = ccpLerp(this->GetEntity()->getPosition(), player->getPosition(), dt * 0.1);
		this->GetEntity()->setPosition(pos);

		mStopWatch->OnUpdate(dt);

		if (mStopWatch->GetAccTime() > 4)
		{
			this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_SeqAttack);
			mStopWatch->OnReset();
		}


	}
}

void JugglerIdleState::OnExit()
{

}

#pragma endregion

#pragma region SeqAttack

bool JugglerSeqAttackState::InitState()
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

JugglerSeqAttackState::~JugglerSeqAttackState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerSeqAttackState::OnEnter()
{
	for (int i = 0; i < this->GetEntity<Juggler>()->GetCircleCount(); i++)
	{
		auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(i);
		circle->SetState(JugglerCircle::State::State_None);
	}
}

void JugglerSeqAttackState::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	if (mCurrentAttackIndex < this->GetEntity<Juggler>()->GetCircleCount())
	{
		if (mStopWatch->GetAccTime() >= 0.8)
		{
			auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(mCurrentAttackIndex);
			Vec2 targetPos = ActorManager::GetInstance()->ConvertPlayerToEntity(mEntity);
			circle->OnAttack(targetPos, 1.8);
			mCurrentAttackIndex++;
			if (mCurrentAttackIndex >= this->GetEntity<Juggler>()->GetCircleCount())
			{
				mCurrentAttackIndex = 0;
				this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_Idle);
			}

			mStopWatch->OnReset();
		}
	}
	/*if (isShot == false)
	{
	if (mStopWatch->GetAccTime() > 2)
	{
	Vec2 targetPos = ActorManager::GetInstance()->ConvertPlayerToEntity(mEntity);

	auto circles = this->GetEntity<Juggler>();
	((JugglerCircle*)circles->GetPartsMap()->at(0))->OnAttack(targetPos, 4);

	isShot = true;
	mStopWatch->OnReset();
	}
	}*/
}

void JugglerSeqAttackState::OnExit()
{
}
#pragma endregion
