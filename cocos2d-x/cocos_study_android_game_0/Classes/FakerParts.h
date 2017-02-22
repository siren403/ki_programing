#ifndef __FAKERPARTS_H__
#define __FAKERPARTS_H__

#include "EnemyParts.h"

class StopWatch;

class FakerSheep : public EnemyParts
{
public:
	enum FaceType
	{
		Face_None = 0,
		Face_1 = 1,
		Face_2 = 2,
		Face_3 = 3,
		Face_4 = 4,
		Face_5 = 5,
	};
	enum State
	{
		State_None = 0,
		State_Idle = 1,
		State_DirMove = 2,
		State_Hide = 3,
	};
private:
	Sprite * mFaceSprite = nullptr;
	StopWatch * mMoveWatch = nullptr;
	StopWatch * mHideWatch = nullptr;
	
	FakerSheep::FaceType mFaceType;
	FakerSheep::State mState;

	//Move
	Vec2 mMoveDirection;
	float mMoveSpeed;
	Vec2 mOriginPosition;
	float mJumpHeight = 0;
	//Hide
	float mHideDuration = 0;

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateHide(float dt);

	void SetSpriteAlpha(float alpha);
public:
	CREATE_FUNC(FakerSheep);
	virtual bool init() override;
	virtual void update(float dt) override;

	void SetState(FakerSheep::State state);
	void SetFace(FaceType type);
	void SetMoveDirection(Vec2 dir);
	void SetMoveDirection(float angle);
	void SetMoveSpeed(float speed);
	void SetOriginPosition(Vec2 pos);
	float GetHideDuration();

	void OnHidePosition();
};


#endif // !__FAKERPARTS_H__
