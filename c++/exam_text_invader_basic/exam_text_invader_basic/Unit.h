#pragma once


class CUnit
{
protected:
	char mDisplayMark = 0;
	int mX = 0;
	int mY = 0;
	float mDirX = 0;
	float mDirY = 0;
	float mSpeedPower = 0;
	bool mIsAlive = true;
public:
	CUnit();
	virtual ~CUnit();

	virtual void SetUp(int tX, int tY);
	virtual void Update();
	virtual void Display(char *tpPixel) = 0;
	virtual void Clean(char *tpPixel);
	virtual void SetAlive(bool tAlive);
	virtual bool GetAlive();


	int GetX();
	void SetX(int tX);
	int GetY();
	void SetY(int tY);
	float GetSpeedPower();
	void SetSpeedPower(float tSpeedPower);
	void SetDirectionAndSpeedPower(float tDirX, float tDirY, float tSpeedPower);

	void SetDisplayMark(char tMark);

	virtual void Destroy() = 0;
};

