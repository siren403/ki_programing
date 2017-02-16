#ifndef __JUGGLERFINITESTATE_H__
#define __JUGGLERFINITESTATE_H__

#include "EnemyFiniteState.h"
#include "cocos2d.h"

using namespace cocos2d;

#pragma region Idle

class JugglerIdleState : public EnemyFiniteState
{
public:
	CREATE_STATE_FUNC(JugglerIdleState);
	virtual bool InitState() override;
	virtual ~JugglerIdleState();

protected:
	virtual void OnEnter() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnExit() override;

};

#pragma endregion


#endif // !__JUGGLERFINITESTATE_H__
