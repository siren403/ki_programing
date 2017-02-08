#ifndef __BOSSHEAD_H__
#define __BOSSHEAD_H__

#include "EnemyParts.h"

class BossHead : public EnemyParts
{
public:
	CREATE_FUNC(BossHead);
	virtual bool init() override;
	virtual void update(float dt) override;

	virtual const Size GetPartsSize() override;
};


#endif // !__BOSSHEAD_H__
