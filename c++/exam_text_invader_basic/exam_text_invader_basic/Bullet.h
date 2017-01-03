#pragma once
#include "Unit.h"


class CBullet :
	public CUnit
{
protected:

public:
	CBullet();
	virtual ~CBullet();


	virtual void Display(char *tpPixel) override;

	void SetPositionForFire(int tX, int tY);

	virtual void Destroy() override;

};

