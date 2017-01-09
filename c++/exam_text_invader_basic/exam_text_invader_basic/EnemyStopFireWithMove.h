#pragma once
#include "Enemy.h"
class CEnemyStopFireWithMove :
	public CEnemy
{
private:
	enum
	{
		STATE_FIRE = 0,
		STATE_MOVE = 1,
	};

	int mCurrentState = 0;
public:
	CEnemyStopFireWithMove();
	~CEnemyStopFireWithMove();

	virtual void Update() override;
	virtual void Shot() override;
};

