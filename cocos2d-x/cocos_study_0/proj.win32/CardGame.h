#ifndef __CARDGAME_SCENE_H__
#define __CARDGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CCardGame : public Layer
{
private:
	//Title
	Layer * mTitleLayer = NULL;
	Label * mTitleLabel = NULL;

	//Battle
	Layer * mBattleLayer = NULL;
	Sprite * mPlayerSprite = NULL;
	
	Layer * mSlimeLayer = NULL;
	Sprite * mSlimeSprite = NULL;
	Sprite * mSlimeHpSprite = NULL;
	
	int mSlimeHp = 0;
	int mSlimeMaxHp = 10;


	Layer * mBossLayer = NULL;
	Sprite * mBossSprite = NULL;
	Sprite * mLeftCard = NULL;
	Sprite * mRightCard = NULL;
	Label * mResultLabel = NULL;

	Label * mLeftWinCountLabel = NULL;
	Label * mRightWinCountLabel = NULL;

	int mLeftWinCount = 0;
	int mRightWinCount = 0;
	int mWinCount = 3;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(CCardGame);

	void DoAction(Ref* pSender);

	void startGame();
	void attackSlime(Ref * pSender);
	void endGame();
};

#endif // !__HELLOWORLD_SCENE_H__
