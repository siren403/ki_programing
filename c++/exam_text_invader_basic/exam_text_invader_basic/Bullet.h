#pragma once
#include "Unit.h"


class CBullet :
	public CUnit
{
protected:
	bool IsScreenOut();
public:
	CBullet();
	virtual ~CBullet();


	virtual void Display(char *tpPixel) override;
	virtual void Destroy() override;

	virtual void SetPositionForFire(int tX, int tY);

	void SetDirectionAndSpeedPower(float tDirX, float tDirY, float tSpeedPower);
};

