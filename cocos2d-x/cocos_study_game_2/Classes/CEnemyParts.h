#ifndef __CENEMYPARTS_H__
#define __CENEMYPARTS_H__

#include "cocos2d.h"
#include "CUnit.h"

using namespace cocos2d;

class CEnemyParts : public CUnit
{
private:
	Sprite * mSprite = nullptr;
	int mHP = 0;
	float mHitDelay = 0;
	float mCurrentHitDelay = 0;

public:
	CREATE_FUNC(CEnemyParts);
	virtual bool init() override;
	virtual void update(float dt) override;

	void setHP(int tHP);
	Sprite * getSprite() const;
	void Hit();
};


#endif // !__CENEMYPARTS_H__
