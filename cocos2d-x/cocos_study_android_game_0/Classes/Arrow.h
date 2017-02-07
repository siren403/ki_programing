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
	//발사 각도(라디안) 
	float mShotRadian = 0;
	//최대 속력
	float mMaxSpeedPower = 0;
	//현재 속력
	float mCurrentSpeedPower = 0;
	//최대 속력를 기준으로 감속 할 비율
	float mDecelRatio = 0;

	//각 상태 별 업데이트
	void updateLock(float dt);
	void updateShot(float dt);
	void updateDrop(float dt);
public:
	CREATE_FUNC(Arrow);
	
	virtual bool init() override;
	virtual void update(float dt) override;

	//get,set


	void InitWithPlayer(Player * player);
	void LockOn(float radian);
	void DisableLockOn();
	void Shot();
};

#endif // !__ARROW_H__
