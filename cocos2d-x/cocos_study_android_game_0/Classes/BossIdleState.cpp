//#include "BossIdleState.h"
//#include "Boss.h"
//#include "BossHand.h"
//#include "BossHead.h"
//
//#define PI 3.14159
//
//
////BossIdleState::BossIdleState(Enemy * entity) : EnemyFiniteState(entity)
////{
////	auto boss = this->GetEntity<Boss>();
////
////	mLHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_LHand);
////	mRHand = (BossHand *)boss->GetParts(Boss::Parts::Parts_RHand);
////	mHead = (BossHead *)boss->GetParts(Boss::Parts::Parts_Head);
////
////	float headDuration = 1.5;
////	auto tIdleSeq = Sequence::create(
////		MoveBy::create(headDuration * 0.5, Vec2(0, 5)),
////		MoveBy::create(headDuration * 0.5, Vec2(0, -5)),
////		nullptr
////	);
////	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
////	mHeadAction = mHead->runAction(tRepeatIdle);
////}
//
//bool BossIdleState::InitState()
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
//	mHead = (BossHead *)boss->GetParts(Boss::Parts::Parts_Head);
//
//	float headDuration = 1.5;
//	auto tIdleSeq = Sequence::create(
//		MoveBy::create(headDuration * 0.5, Vec2(0, 5)),
//		MoveBy::create(headDuration * 0.5, Vec2(0, -5)),
//		nullptr
//	);
//	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
//	mHeadAction = mHead->runAction(tRepeatIdle);
//	return true;
//}
//
//void BossIdleState::OnEnter()
//{
//	//auto seq = Sequence::create(
//	//	DelayTime::create(0.5),
//	//	CallFunc::create([lefthand, this]()
//	//{
//	//	//플레이어와 보스는 같은 부모에 속해있기 때문에
//	//	//보스의 부모를 기준으로 월드 포지션으로 변환 후
//	//	Vec2 pos = getParent()->convertToWorldSpace(ActorManager::GetInstance()->GetPlayer()->getPosition());
//	//	//변환한 포지션을 보스의 로컬포지션을 사용하는 하위 계층에게
//	//	//올바르게 전달하기 위해 보스의 로컨 포지션으로 변환 후 전달한다.
//	//	pos = convertToNodeSpace(pos);
//	//	lefthand->OnAttack(pos);
//	//}),
//	//	DelayTime::create(0.5),
//	//	CallFunc::create([righthand, this]()
//	//{
//	//	//플레이어와 보스는 같은 부모에 속해있기 때문에
//	//	//보스의 부모를 기준으로 월드 포지션으로 변환 후
//	//	Vec2 pos = getParent()->convertToWorldSpace(ActorManager::GetInstance()->GetPlayer()->getPosition());
//	//	//변환한 포지션을 보스의 로컬포지션을 사용하는 하위 계층에게
//	//	//올바르게 전달하기 위해 보스의 로컨 포지션으로 변환 후 전달한다.
//	//	pos = convertToNodeSpace(pos);
//	//	righthand->OnAttack(pos);
//	//}),
//	//	nullptr
//	//	);
//	//this->runAction(seq);
//}
//
//void BossIdleState::OnUpdate(float dt)
//{
//	HandIdleMotion(mLHand, mLHandRadian, dt);
//	HandIdleMotion(mRHand, mRHandRadian, dt);
//
//	mCurrentTime += dt;
//	if (mCurrentTime >= 1)
//	{
//		mCurrentTime = 0;
//		this->GetEntity<Boss>()->ChangeState(Boss::State::State_HandAttack);
//	}
//}
//
//void BossIdleState::OnExit()
//{
//	//mHead->stopAction(mHeadAction);
//}
//
//void BossIdleState::HandIdleMotion(BossHand * hand, float & radian, float dt)
//{
//	Vec2 pos;
//
//	pos = hand->GetInitPosition();
//	radian += (PI * dt) * -1;
//	if (radian <= PI * -2)
//	{
//		radian = 0;
//	}
//	pos.x += (cos(radian) * 10) * hand->GetHandDirection();
//	pos.y += sin(radian) * 10;
//	hand->setPosition(pos);
//}
//
//
//
//BossIdleState::~BossIdleState()
//{
//
//}
