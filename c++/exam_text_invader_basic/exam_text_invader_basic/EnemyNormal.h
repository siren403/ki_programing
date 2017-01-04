#pragma once
#include "Enemy.h"
class CEnemyNormal :
	public CEnemy
{
public:
	CEnemyNormal();
	~CEnemyNormal();

	virtual void Update() override;

};

