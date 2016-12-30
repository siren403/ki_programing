#pragma once
#include "MapManager.h"
#include "Player.h"
#include "Slime.h"
#include "BossSlime.h"
#include "CharacterFactory.h"
#include "defines.h"

class CGameManager
{
private:
	int mGameState = 0;//게임시작 시 타이틀 상태
	int mInput = 0;//Input입력 받는 변수
	char mIsContinue = 0;

	CMapManager mMap;
	CPlayer *mPlayer = NULL;
	CSlime *mNormalSlime = NULL;
	CBossSlie *mBossSlime = NULL;

	CCharacterFactory mCharacterFactory;
public:
	CGameManager();
	~CGameManager();

	CPlayer& GetPlayer();
	CMonster& GetMonster(int tKind);
	void Play();


private:
	int DisplayTitle();

};

