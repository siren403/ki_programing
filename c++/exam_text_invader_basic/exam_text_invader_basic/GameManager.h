#pragma once

#include "config.h"

#include "Actor.h"
#include "Enemy.h"
#include "EnemyBullet.h"

#include <vector>

using namespace std;

class GameManager
{
private:
	
	typedef void(GameManager::*StateAction)();
	
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
	StateAction mStateActions[4];


	int mRow = 0;
	int mCol = 0;
	char mKey = 0;
	char tPixel[HEIGHT][WIDTH] = { 0 };


	CActor mActor;
	vector<CEnemy*> mEnemys;


	void Init();
	void Title();
	void Update();
	void Display();
	void Quit();

	void ClearScreen(int tX, int tY);
public:
	GameManager();
	~GameManager();

	void Play();

};

