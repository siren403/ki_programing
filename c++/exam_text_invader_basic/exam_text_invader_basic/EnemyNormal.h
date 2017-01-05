#pragma once
#include "Enemy.h"
class CEnemyNormal :
	public CEnemy
{
private:
	int mMoveWidth = 5;
	int mStartPositionX = 0;
public:
	CEnemyNormal();
	~CEnemyNormal();

	virtual void Update() override;
	virtual void SetUp(int tX, int tY) override;

	void SetMoveWidth(int tMoveWidth);

};

