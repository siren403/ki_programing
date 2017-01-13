#ifndef __SCENEFIELD_H__
#define __SCENEFIELD_H__

#include "cocos2d.h"


USING_NS_CC;

class SpriteAnimator;
class Dice;


class SceneField : public LayerColor
{

private:
	//Battle
	Layer * mpBattleLayer = nullptr;


	int mSlimeHp = 0;
	Layer * mpSlimeLayer = nullptr;
	Sprite * mpSlimeSprite = nullptr;
	Sprite * mpSlimeHpSprite = nullptr;
	Dice * mpDice = nullptr;

	int mSlimeMaxHp = 10;
	Layer * mpBossLayer = nullptr;
	Sprite * mpBossSprite = nullptr;
	Sprite * mpLeftCard = nullptr;
	Sprite * mpRightCard = nullptr;
	Label * mpResultLabel = nullptr;

	Label * mpLeftWinCountLabel = nullptr;
	Label * mpRightWinCountLabel = nullptr;

	int mLeftWinCount = 0;
	int mRightWinCount = 0;
	int mWinCount = 3;
public:
	void attackSlime();
	void doAction(Ref* pSender);

	//==========================================
private:
	SpriteAnimator * mpPlayerAnimator = nullptr;
	EventListenerTouchOneByOne * mpTouchEventOne = nullptr;
	void NextScene();
public:
	static Scene * createScene();

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual bool onTouchBegan(Touch * tTouch, Event * unused_event) override;

	CREATE_FUNC(SceneField);

};

#endif // !__SCENEFIELD_H__
