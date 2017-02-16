#include "Boss.h"
#include "BossParts.h"
#include "BossFiniteState.h"

#include "ActorManager.h"
#include "Player.h"

bool Boss::init()
{
	if (!Enemy::init())
	{
		return true;
	}

	auto body = BossBody::create();
	this->AddParts(Parts::Parts_Body, body);

	auto head = BossHead::create();
	head->setPosition(0, body->GetPartsSize().height* 0.55);
	this->AddParts(Parts::Parts_Head, head, true);

	auto lefthand = BossHand::create();
	lefthand->InitHand(BossHand::HandDir::HandDir_Left);
	lefthand->setPosition(body->GetPartsSize().width * -0.6, body->GetPartsSize().height * -0.3);
	lefthand->SetAttackDuration(1.8);
	this->AddParts(Parts::Parts_LHand, lefthand);

	auto righthand = BossHand::create();
	righthand->InitHand(BossHand::HandDir::HandDir_Right);
	righthand->setPosition(body->GetPartsSize().width * 0.6, body->GetPartsSize().height * -0.3);
	righthand->SetAttackDuration(1.5);
	this->AddParts(Parts::Parts_RHand, righthand);

	this->setScale(1.5 * CC_CONTENT_SCALE_FACTOR());

	this->AddState(State::State_Idle, BossIdleState::Create(this));
	this->AddState(State::State_HandAttack, BossHandAttackState::Create(this));

	this->ChangeState(State::State_Idle);

	return true;
}

void Boss::OnActivate(bool isActive)
{
	//this->GetState<BossIdleState>(State::State_Idle)->SetActive(isActive);
	if (isActive == false)
	{
		this->ChangeState(State::State_Idle);
		if (mLifeParts != nullptr)
		{
			mLifeParts->SetAlive(true);
		}
	}

	auto idle = (BossIdleState *)this->GetState(State::State_Idle);
	idle->SetActive(isActive);
	
}

