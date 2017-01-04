#pragma once

#include "config.h"

#include "Actor.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "EnemyFactory.h"
#include <vector>

using namespace std;

class CGameManager
{
private:
	
	typedef void(CGameManager::*StateAction)();
	
	enum 
	{
		STATE_INIT = 0,
		STATE_TITLE = 1,
		STATE_UPDATE = 2,
		STATE_DISPLAY = 3,

		STATE_QUIT = 4,
	};
	
	int mCurrentState = 0;
	bool mIsPlaying = false;
	StateAction mStateActions[STATE_QUIT + 1];


	int mRow = 0;
	int mCol = 0;
	char mKey = 0;
	char tPixel[HEIGHT][WIDTH] = { 0 };


	CActor mActor;
	vector<CEnemy*> *mEnemys;
	vector<CEnemyFactory*> mEnemyFactorys;
	int mCurrentFactory = 0;

	void Init();
	void Title();
	void Update();
	void Display();
	void Quit();

	void ClearScreen(int tX, int tY);
public:
	CGameManager();
	~CGameManager();

	void Play();

	void SetEnemys(vector<CEnemy*> *tpEnemys);
	void SetFactory(int tIndex);
};

