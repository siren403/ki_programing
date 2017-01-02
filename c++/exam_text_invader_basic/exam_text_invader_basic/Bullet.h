#pragma once
#include "Character.h"


class CBullet :
	public CCharacter
{
protected:
	bool mIsAlive = false;
	char mMark = 0;

public:
	CBullet();
	virtual ~CBullet();


	virtual void Display(char *tpPixel) override;

	void SetPositionForFire(int tX, int tY);

	void SetAlive(bool tAlive);
	bool GetAlive();
};

