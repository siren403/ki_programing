#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class Player;

class Arrow : public Actor
{
private:
	enum State
	{
		State_Idle = 0,
		State_LockOn = 1,
		State_Shot = 2,
		State_Drop = 3,
	};
	
	Sprite * mSprite = nullptr;
	Player * mPlayer = nullptr;

	State mState;
	float mShotRadian = 0;
	float mMaxSpeed = 0;
	float mCurrentSpped = 0;


	void updateLock(float dt);
	void updateShot(float dt);
public:
	CREATE_FUNC(Arrow);
	
	virtual bool init() override;
	virtual void update(float dt) override;

	void InitWithPlayer(Player * player);
	void LockOn(float radian);
	void DisableLockOn();
	void Shot();
};

#endif // !__ARROW_H__
