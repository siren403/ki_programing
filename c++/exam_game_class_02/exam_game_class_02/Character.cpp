#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

int Character::GetHealth()
{
	return mHealth;
}

int & Character::GetCurrentHealth()
{
	return mCurrentHealth;
}

int & Character::GetPower()
{
	return mPower;
}

void Character::SetHealth(int tHealth)
{
	mHealth = tHealth;
}

void Character::SetCurrentHealth(int tCurHealth)
{
	mCurrentHealth = tCurHealth;
}

void Character::SetPower(int tPower)
{
	mPower = tPower;
}

void Character::DoAttack(Character * tTarget)
{
	tTarget->SetCurrentHealth(tTarget->GetCurrentHealth() - mPower);
	if (tTarget->GetCurrentHealth() < 0)
	{
		tTarget->SetCurrentHealth(0);
	}
}


