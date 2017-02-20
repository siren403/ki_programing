#ifndef __FAKER_H__
#define __FAKER_H__

#include "Enemy.h"

class Faker : public Enemy
{
public:
	enum State
	{
		None = 0,
		Idle = 1,
	};
private:
	Faker::State mState;
public:
	CREATE_FUNC(Faker);
	virtual bool init() override;

	virtual void OnActivate(bool isActive) override;

};

#endif // !__FAKER_H__
