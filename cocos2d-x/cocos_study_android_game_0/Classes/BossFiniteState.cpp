#include "BossFiniteState.h"

#include "Boss.h"
#include "BossParts.h"

#include "ActorManager.h"
#include "Player.h"

#define PI 3.14159

bool BossIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	auto boss = this->GetEntity<Boss>();

	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);
	mHead = (BossHead *)boss->GetParts(Boss::Parts::Parts_Head);

	float headDuration = 1.5;
	auto tIdleSeq = Sequence::create(
		MoveBy::create(headDuration * 0.5, Vec2(0, 5)),
		MoveBy::create(headDuration * 0.5, Vec2(0, -5)),
		nullptr
	);
	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
	mHeadAction = mHead->runAction(tRepeatIdle);

	return true;
}

void BossIdleState::OnEnter()
{
}

void BossIdleState::OnUpdate(float dt)
{
	HandIdleMotion(mLHand, mLHandRadian, dt);
	HandIdleMotion(mRHand, mRHandRadian, dt);

	mCurrentTime += dt;
	if (mCurrentTime >= 1)
	{
		mCurrentTime = 0;
		this->GetEntity<Boss>()->ChangeState(Boss::State::State_HandAttack);
	}
}
void BossIdleState::HandIdleMotion(BossHand * hand, float & radian, float dt)
{
	Vec2 pos;

	pos = hand->GetInitPosition();
	radian += (PI * dt) * -1;
	if (radian <= PI * -2)
	{
		radian = 0;
	}
	pos.x += (cos(radian) * 10) * hand->GetHandDirection();
	pos.y += sin(radian) * 10;
	hand->setPosition(pos);
}

void BossIdleState::OnExit()
{
	mHead->stopAction(mHeadAction);
}

BossIdleState::~BossIdleState()
{
}






bool BossHandAttackState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	auto boss = this->GetEntity<Boss>();

	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);

	mAttackDelay = 1.5;
	mCurrentTime = mAttackDelay;

	return true;
}
void BossHandAttackState::OnEnter()
{
	auto player = ActorManager::GetInstance()->GetPlayer();
	Vec2 targetPos = player->getParent()->convertToWorldSpace(player->getPosition());
	targetPos = mEntity->convertToNodeSpace(targetPos);
	mLHand->OnAttack(targetPos);
}

void BossHandAttackState::OnUpdate(float dt)
{
	if (mCurrentTime >= mAttackDelay)
	{
		mAttackDelay = 0;
		//log("Attack");
	}
}

void BossHandAttackState::OnExit()
{
}

BossHandAttackState::~BossHandAttackState()
{
}
