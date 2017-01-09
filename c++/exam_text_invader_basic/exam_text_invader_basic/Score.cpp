#include "stdafx.h"
#include "Score.h"
#include "config.h"

#include <iostream>

using namespace std;

CScore *CScore::mInstance = NULL;

CScore::CScore()
{
	mTimer.SetInterval(1000);
	mScoreIncrementRate = 1238;
	mCurrentScore = 0;
	mScoreNumbers.reserve(10);
	mTitle = "SCORE : ";
}


CScore::~CScore()
{
}

CScore & CScore::GetInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new CScore();
	}

	return *mInstance;
}

void CScore::ScoreUpdate()
{
	mTimer.Update();
	if (mTimer.Check())
	{
		mCurrentScore += mScoreIncrementRate;
	}
}

void CScore::Display(char * tpPixel)
{
	ScoreUpdate();

	int tN = mCurrentScore;
	while (tN > 0)
	{
		mScoreNumbers.push_back(tN % 10);
		tN /= 10;
	}

	int tCount = 0;

	for (int ti = 0; ti < mTitle.length(); ti++)
	{
		*(tpPixel + mY * WIDTH + (mX + tCount)) = mTitle[ti];
		tCount++;
	}

	for (vector<int>::reverse_iterator i = mScoreNumbers.rbegin(); i != mScoreNumbers.rend(); i++)
	{
		*(tpPixel + mY * WIDTH + (mX + tCount)) = *i + 48;
		tCount++;
	}
	mScoreNumbers.clear();

}

void CScore::SetPosition(int tX, int tY)
{
	mX = tX;
	mY = tY;
}
