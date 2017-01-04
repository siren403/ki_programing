#pragma once
#include "Enemy.h"
class CEnemyStopFireWithMove :
	public CEnemy
{
public:
	CEnemyStopFireWithMove();
	~CEnemyStopFireWithMove();

	virtual void Update() override;
};

