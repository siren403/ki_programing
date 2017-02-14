#ifndef __BOSSBODY_H__
#define __BOSSBODY_H__

#include "EnemyParts.h"


class BossBody : public EnemyParts
{
public:
	CREATE_FUNC(BossBody);
	virtual bool init() override;

	virtual const Size GetPartsSize() override;
};

#endif // !__BOSSBODY_H__
