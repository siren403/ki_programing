#include "stdafx.h"
#include "EnemyFactory.h"
#include "GameManager.h"


CEnemyFactory::CEnemyFactory()
{
}


CEnemyFactory::~CEnemyFactory()
{
}

void CEnemyFactory::DoSetting(CGameManager & tGameManager)
{
	tGameManager.SetEnemys(&mEnemys);
}

void CEnemyFactory::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mEnemys.size(); ti++)
	{
		if (mEnemys[ti] != NULL)
		{
			mEnemys[ti]->Destroy();
		}
	}
	mEnemys.clear();

	delete this;
}


