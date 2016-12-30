#pragma once
class CCharacter
{
protected:
	int mX = 0;
	int mY = 0;
	int mWidth = 0;
	int mHeight = 0;
public:
	CCharacter();
	~CCharacter();

	virtual void SetUp(int tWidth, int tHeight);
	void Clean(char *tpPixel);
	virtual void Display(char *tpPixel) = 0;
	int GetX();
	void SetX(int);

	int GetY();
	void SetY(int);
};

