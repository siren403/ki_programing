#ifndef __FAKER_H__
#define __FAKER_H__

#include "Enemy.h"

#define LIFEPARTS_KEY -1

class Faker : public Enemy
{
public:
	enum State
	{
		State_None = 0,
		State_Idle = 1,
		State_ShowLife = 2,
		State_AllHide = 3,
		State_AllSideShow = 4,
	};
private:
	Faker::State mState;
public:
	CREATE_FUNC(Faker);
	virtual bool init() override;

	virtual void OnActivate(bool isActive) override;

};

#endif // !__FAKER_H__
