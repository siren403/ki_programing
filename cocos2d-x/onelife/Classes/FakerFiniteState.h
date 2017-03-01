#ifndef __FAKERFINITESTATE_H__
#define __FAKERFINITESTATE_H__

#include "EnemyFiniteState.h"

class StopWatch;

#pragma region Idle

class FakerIdleState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(FakerIdleState);
	virtual bool InitState() override;
	virtual ~FakerIdleState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	StopWatch * mStopWatch = nullptr;
};

#pragma endregion


#pragma region ShowLife

class FakerShowLifeState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(FakerShowLifeState);
	virtual bool InitState() override;
	virtual ~FakerShowLifeState();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	StopWatch * mStopWatch = nullptr;
};

#pragma endregion

#pragma region AllHide

class FakerAllHide : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(FakerAllHide);
	virtual bool InitState() override;
	virtual ~FakerAllHide();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	StopWatch * mStopWatch = nullptr;
	float mSheepHideDuration = 0;

};

#pragma endregion

#pragma region AllSideShow

class FakerAllSideShow : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(FakerAllSideShow);
	virtual bool InitState() override;
	virtual ~FakerAllSideShow();
protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;
private:
	StopWatch * mStopWatch = nullptr;
};

#pragma endregion



#endif // !__FAKERFINITESTATE_H__
