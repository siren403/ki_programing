#pragma once
#include "Character.h"


class CBullet :
	public CCharacter
{
private:
	bool mIsLife = false;
	int mDir = 0;

public:
	CBullet();
	~CBullet();

	enum {
		DIR_UP = -1,
		DIR_DOWN = 1,
	};

	virtual void Display(char *tpPixel) override;
	void Shot();
	void Move();

	void SetDir(int tDir);
	bool GetIsLife();
};

