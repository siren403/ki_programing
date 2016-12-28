#pragma once
class CDice
{
private:
	int mDiceNumber = 0;


public:
	CDice();
	~CDice();

	int DoThrow(int tMaxNumber);
	int GetDiceNumber();
};

