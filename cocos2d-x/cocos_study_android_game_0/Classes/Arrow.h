#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"
#include "Actor.h"

#pragma execution_character_set("utf-8")

using namespace cocos2d;

class Player;

class Arrow : public Actor
{
public:
	enum State
	{
		State_Idle = 0,
		State_LockOn = 1,
		State_Shot = 2,
		State_Drop = 3,
	};
private:

	Sprite * mSprite = nullptr;
	Player * mPlayer = nullptr;

	State mState;
	//발사 방향
	Vec2 mMoveDirection;

	//최대 속력
	float mMaxSpeedPower = 0;
	//현재 속력
	float mCurrentSpeedPower = 0;
	//최대 속력를 기준으로 감속 할 비율
	float mDecelRatio = 0;

	//충돌
	bool mIsPrevCollision = false;
	bool mIsCollision = false;

	bool mIsReturnArrow = false;

	//각 상태 별 업데이트
	void updateLock(float dt);
	void updateShot(float dt);
	void updateDrop(float dt);

public:
	CREATE_FUNC(Arrow);

	virtual bool init() override;
	virtual void update(float dt) override;

	//get,set
	Arrow::State GetState();
	Vec2 GetMoveDirection();
	void SetReturnArrow(bool isReturn);


	void InitWithPlayer(Player * player);
	void LockOn(Vec2 dir);
	void DisableLockOn();
	void Shot();

	virtual void OnCollisionOther(bool isCollision, Node * other,Vec2 normal = Vec2::ZERO) override;
	bool IsShooting();
};

#endif // !__ARROW_H__
