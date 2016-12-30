#pragma once
#include "Character.h"

#define DIR_LEFT 0
#define DIR_RIGHT 1

class CEnemy :
	public CCharacter
{
private:
	int mDir = 0;
public:
	CEnemy();
	~CEnemy();

	virtual void SetUp(int tWidth, int tHeight) override;
	virtual void Display(char *tpPixel) override;

	void Move();

};

