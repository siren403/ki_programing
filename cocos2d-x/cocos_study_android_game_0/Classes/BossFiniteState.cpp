#include "BossFiniteState.h"

#include "Boss.h"
#include "BossParts.h"

#include "ActorManager.h"
#include "Player.h"

#define PI 3.14159
#define EPSILON 0.001

#pragma region Idle


bool BossIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	auto boss = this->GetEntity<Boss>();

	return true;
}

void BossIdleState::OnEnter()
{
	
}

void BossIdleState::OnUpdate(float dt)
{
	if (mIsActive)
	{
		mCurrentTime += dt;
		if (mCurrentTime >= 1.5)
		{
			mCurrentTime = 0;
			this->GetEntity<Boss>()->ChangeState(Boss::State::State_HandAttack);
		}
	}
}

void BossIdleState::OnExit()
{
	mCurrentTime = 0;
}

BossIdleState::~BossIdleState()
{
}


#pragma endregion



#pragma region HandAttack

bool BossHandAttackState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	auto boss = this->GetEntity<Boss>();

	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);

	mCurrentTime = 0;

	return true;
}

void BossHandAttackState::OnEnter()
{
	HandAttacKLockOn(mLHand);
}

void BossHandAttackState::OnUpdate(float dt)
{
	mCurrentTime += dt;

	if (mIsSecondAttack == false)
	{
		if (mCurrentTime >= 2)
		{
			HandAttacKLockOn(mRHand);
			mIsSecondAttack = true;
			mCurrentTime = 0;
		}
	}
	else
	{
		if (mCurrentTime >= 2)
		{
			this->GetEntity<Boss>()->ChangeState(Boss::State::State_Idle);
		}
	}
}
void BossHandAttackState::HandAttacKLockOn(BossHand * hand)
{
	auto player = ActorManager::GetInstance()->GetPlayer();
	Vec2 targetPos = player->getParent()->convertToWorldSpace(player->getPosition());
	targetPos = mEntity->convertToNodeSpace(targetPos);
	hand->OnAttack(targetPos);
}

void BossHandAttackState::OnExit()
{
	mIsSecondAttack = false;
	mCurrentTime = 0;
}

BossHandAttackState::~BossHandAttackState()
{

}

#pragma endregion
