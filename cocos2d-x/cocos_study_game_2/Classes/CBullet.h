#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "cocos2d.h"
#include "CUnit.h"

using namespace cocos2d;

class CBullet : public CUnit
{
protected:
	Vec2 mCurrenDir;
	float mCurrentSpeed = 0;
	bool mIsAlive = false;
	
	
	bool isScreenOut();
	void setIsAlive(bool tIsAlive);
	
	virtual void bulletUpdate(float dt);
public:
	CREATE_FUNC(CBullet);
	virtual bool lateInit() override;
	virtual void update(float dt) override;

	void setSprite(Sprite * tSprite);

	void setDirection(Vec2 tDir);
	void setSpeed(float tSpeed);

	bool getIsAlive();

	void Shot(Vec2 tPos);
};

#endif // !__CBULLET_H__
