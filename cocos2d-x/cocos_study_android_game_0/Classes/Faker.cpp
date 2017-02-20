#include "Faker.h"
#include "FakerParts.h"
#include "FakerFiniteState.h"

#define LIFEPARTS_KEY -1


bool Faker::init()
{
	if (!Enemy::init())
	{
		return false;
	}

	auto lifeParts = FakerSheep::create();
	//lifeParts->GetSprite()->setColor(Color3B::RED);
	this->AddParts(LIFEPARTS_KEY, lifeParts, true);

	

	this->AddState(Faker::State::Idle, FakerIdleState::Create(this));
	this->ChangeState(Faker::State::Idle);

	return true;
}

void Faker::OnActivate(bool isActive)
{
	this->GetState(Faker::State::Idle)->SetActive(isActive);
}
