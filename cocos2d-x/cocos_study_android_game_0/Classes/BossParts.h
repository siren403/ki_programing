#pragma once

#include "EnemyParts.h"

#pragma region Head

class BossHead : public EnemyParts
{
private:
	Action * mHeadAction = nullptr;
public:
	CREATE_FUNC(BossHead);
	virtual bool init() override;

	virtual const Size GetPartsSize() override;
};
#pragma endregion

#pragma region Body


class BossBody : public EnemyParts
{
public:
	CREATE_FUNC(BossBody);
	virtual bool init() override;

	virtual const Size GetPartsSize() override;
};
#pragma endregion

#pragma region Hand

class BossHand : public EnemyParts
{
public:
	enum HandDir
	{
		HandDir_Left = -1,
		HandDir_Right = 1,
	};
private:
	enum State
	{
		Idle = 0,
		Attack_Shot = 1,
	};
	BossHand::State mState;

	char mHandDirection = 0;
	Vec2 mInitPosition;

	float mCurrentTime = 0;

	//idle
	float mIdleRadian = 0;

	//attack
	float mAttackDuration = 0;
	Vec2 mAttackTargetPos;

	void UpdateIdle(float dt);
	void UpdateAttack(float dt);
public:
	CREATE_FUNC(BossHand);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;

	void InitHand(HandDir dir);

	//get,set
	Vec2 GetInitPosition();
	char GetHandDirection();
	void SetAttackDuration(float duration);

	void OnAttack(Vec2 pos);
};

#pragma endregion
