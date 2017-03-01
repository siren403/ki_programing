#ifndef __CACTOR_H__
#define __CACTOR_H__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class StopWatch;
class SpriteAnimator;
class ActorManager;
class SWPointColor;

class Player : public Actor
{
	friend ActorManager;
public:
	enum State
	{
		Idle = 0,
		Move = 1,
		Roll = 2,
	};

public:
	//라이프사이클 오버라이드
	virtual bool init() override;
	virtual void update(float dt) override;

	//getter,setter
	Sprite * GetSprite();
	void SetIsControl(bool tIsControl);
	bool GetIsControl();
	void SetMoveDir(Vec2 dir);
	Vec2 GetMoveDir();
	void SetMoveArea(Size area);
	Player::State GetState();

	void OnRoll(float rollRadian);

	virtual void OnCollisionOther(bool isCollision, Node * other, Vec2 normal = Vec2::ZERO) override;

	void InitPosition(Vec2 pos);
private:

	SpriteAnimator * mSpriteAnim = nullptr;
	SWPointColor * mShaderPointColor = nullptr;
	StopWatch * mPointColorWatch = nullptr;

	bool mIsControl = false;
	Player::State mState;

	//move
	float mMoveSpeed = 0;
	Vec2 mMoveDir;
	Vec2 mPrevPos;
	bool mIsVerticalCollision = false;
	bool mIsHorizontalCollision = false;
	//roll
	float mRollDistance;
	float mRollDuration;
	float mRollRadian;
	Action * mRollColorAction = nullptr;

	Vec2 mRollStartPos;
	Vec2 mRollDestPos;
	float mRollCurTime;

	Size mMoveArea;

	void updateMove(float dt);
	void updateRoll(float dt);

	CREATE_FUNC(Player);
	virtual ~Player();
};

#endif // !__CACTOR_H__
