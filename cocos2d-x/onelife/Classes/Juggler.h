#ifndef __JUGGLER_H__
#define __JUGGLER_H__

#include "Enemy.h"
#include <vector>
#define LIFEPARTS_KEY -1

using namespace std;

class Juggler : public Enemy
{
public:
	enum State
	{
		State_None = 0,
		State_Idle = 1,
		State_SeqAttack = 2,
		State_RushAttack = 3,
		State_CornerAttack = 4,
		State_ColRowAttack = 5,
	};
private:
	int mCircleCount = 0;
	float mCircleRadius = 0;
	float mCirclePivot = 0;
	vector<int> mNextStates;
public:
	CREATE_FUNC(Juggler);
	virtual bool init() override;

	virtual void OnActivate(bool isActive) override;

	//get,set
	int GetCircleCount();
	float GetCircleRadius();
	float GetCirclePivot();

	void RandomChangeState();
};

#endif // !__JUGGLER_H__


