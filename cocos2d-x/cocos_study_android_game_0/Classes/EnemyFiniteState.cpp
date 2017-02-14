#include "EnemyFiniteState.h"


bool EnemyFiniteState::InitState()
{
	return true;
}


//EnemyFiniteState::EnemyFiniteState(Enemy * entity) : mEntity(entity)
//{
//}

EnemyFiniteState::~EnemyFiniteState()
{

}


void EnemyFiniteState::OnEnter()
{
	log("enemy finite state : require OnEnter Override");
}

void EnemyFiniteState::OnUpdate(float dt)
{
	log("enemy finite state : require OnUpdate Override");
}

void EnemyFiniteState::OnExit()
{
	log("enemy finite state : require OnExit Override");
}