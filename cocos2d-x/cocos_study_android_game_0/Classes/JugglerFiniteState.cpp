#include "JugglerFiniteState.h"
#include "Juggler.h"
#include "JugglerParts.h"

#include "ActorManager.h"
#include "Player.h"

#pragma region Idle

bool JugglerIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	return true;
}

JugglerIdleState::~JugglerIdleState()
{

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
	auto player = ActorManager::GetInstance()->GetPlayer();
	Vec2 pos;
	pos = ccpLerp(this->GetEntity()->getPosition(), player->getPosition(), dt * 0.1);
	this->GetEntity()->setPosition(pos);
}

void JugglerIdleState::OnExit()
{

}

#pragma endregion
