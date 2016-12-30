#pragma once
class CUnit
{
private:
	int mState = 0;

	typedef void (CUnit::*CallFuncState)(void);

	CallFuncState mArray[2] = { &CUnit::DoIdle,&CUnit::DoAttack };

protected:
	virtual void DoIdle();
	virtual void DoAttack();

public:
	CUnit();
	~CUnit();

	enum { STATE_IDLE = 0, STATE_ATTACK = 1 };

	void SetState(int tState);
	void Execute();
};