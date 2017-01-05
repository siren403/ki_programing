#pragma once
#include "Timer.h"
#include <vector>
#include <string>

using namespace std;

class CScore
{
private:
	static CScore * mInstance;

	int mX = 0;
	int mY = 0;

	unsigned int mScoreIncrementRate = 0;
	unsigned int mCurrentScore = 0;
	
	CTimer mTimer;
	vector<int> mScoreNumbers;
	string mTitle;


	void ScoreUpdate();
public:
	CScore();
	~CScore();

	static CScore & GetInstance();

	void Display(char *tpPixel);
	void SetPosition(int tX, int tY);
};

