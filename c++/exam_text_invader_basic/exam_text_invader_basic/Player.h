#pragma once
#include "Character.h"
class CPlayer :
	public CCharacter
{
public:
	CPlayer();
	~CPlayer();

	virtual void SetUp(int tWidth, int tHeight) override;
	virtual void Display(char *tpPixel) override;

	void MoveActorWithInput(char tKey);
};

