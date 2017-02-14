//#include "BossHandAttackState.h"
//
//#include "Boss.h"
//#include "BossHand.h"
//#include "ActorManager.h"
//#include "Player.h"
//
////BossHandAttackState::BossHandAttackState(Enemy * entity) : EnemyFiniteState(entity)
////{
////	auto boss = this->GetEntity<Boss>();
////
////	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
////	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);
////
////	mAttackDelay = 1.5;
////	mCurrentTime = mAttackDelay;
////}
//bool BossHandAttackState::InitState()
//{
//	if (!EnemyFiniteState::InitState())
//	{
//		return false;
//	}
//
//	auto boss = this->GetEntity<Boss>();
//
//	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
//	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);
//
//	mAttackDelay = 1.5;
//	mCurrentTime = mAttackDelay;
//
//	return true;
//}
//
//void BossHandAttackState::OnEnter()
//{
//	auto player = ActorManager::GetInstance()->GetPlayer();
//	Vec2 targetPos = player->getParent()->convertToWorldSpace(player->getPosition());
//	mLHand->OnAttack(targetPos);
//}
//
//void BossHandAttackState::OnUpdate(float dt)
//{
//	if (mCurrentTime >= mAttackDelay)
//	{
//
//	}
//}
//
//void BossHandAttackState::OnExit()
//{
//
//}
//BossHandAttackState::~BossHandAttackState()
//{
//
//}
//
