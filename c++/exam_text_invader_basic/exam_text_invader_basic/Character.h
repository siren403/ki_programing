#pragma once


class CCharacter
{
protected:
	int mX = 0;
	int mY = 0;
	float mDirX = 0;
	float mDirY = 0;
	float mSpeedPower = 0;
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void SetUp(int tX, int tY);
	virtual void Update();
	virtual void Display(char *tpPixel) = 0;
	virtual void Clean(char *tpPixel);

	int GetX();
	void SetX(int);
	int GetY();
	void SetY(int);
};

