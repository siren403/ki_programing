#include "stdafx.h"
#include "CharacterFactory.h"


CCharacterFactory::CCharacterFactory()
{
	mCreater[STATE_PLAYER] = &CCharacterFactory::CreatePlayer;
	mCreater[STATE_SLIME] = &CCharacterFactory::CreateSlime;
	mCreater[STATE_BOSS_SLIME] = &CCharacterFactory::CreateBossSlime;

}


CCharacterFactory::~CCharacterFactory()
{
}

void CCharacterFactory::SetState(int tState)
{
	mState = tState;
}

Character* CCharacterFactory::Execute()
{
	Character *ptr = NULL;

	ptr = (this->*mCreater[mState])();
	/*
	switch (tCharacterEnum)
	{
	case C_PLAYER:
		ptr = new CPlayer();
		break;
	case C_SLIME:
		ptr = new CSlime();
		break;
	case C_BOSS_SLIME:
		ptr = new CBossSlie();
		break;
	}
	*/

	return ptr;
}


Character * CCharacterFactory::CreatePlayer()
{
	return new CPlayer();
}

Character * CCharacterFactory::CreateSlime()
{
	return new CSlime();
}

Character * CCharacterFactory::CreateBossSlime()
{
	return new CBossSlie();
}
