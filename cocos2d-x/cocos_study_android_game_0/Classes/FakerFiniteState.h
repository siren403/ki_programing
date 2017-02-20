#ifndef __FAKERFINITESTATE_H__
#define __FAKERFINITESTATE_H__

#include "EnemyFiniteState.h"

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
};

#pragma endregion



#endif // !__FAKERFINITESTATE_H__
