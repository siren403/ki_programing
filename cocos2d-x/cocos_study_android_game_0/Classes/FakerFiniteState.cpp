#include "FakerFiniteState.h"

bool FakerIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}


	return true;
}

FakerIdleState::~FakerIdleState()
{
}

void FakerIdleState::OnEnter()
{
}

void FakerIdleState::OnUpdate(float dt)
{
}

void FakerIdleState::OnExit()
{
}
