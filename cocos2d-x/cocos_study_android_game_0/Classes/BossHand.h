#ifndef __BOSSHAND_H__
#define __BOSSHAND_H__

#include "EnemyParts.h"


class BossHand : public EnemyParts
{
public:
	enum HandDir
	{
		HandDir_Left = -1,
		HandDir_Right = 1,
	};
private:
	char mHandDir = 0;
public:
	CREATE_FUNC(BossHand);
	virtual bool init() override;
	virtual void update(float dt) override;

	void InitHand(HandDir dir);
};

#endif // !__BOSSHAND_H__
