#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "cocos2d.h"
#include "CUnit.h"

using namespace cocos2d;

class CEnemy;
class CActor;

class CBullet : public CUnit
{
protected:
	Sprite * mSprite = nullptr;
	Vec2 mCurrenDir;
	float mCurrentSpeed = 0;
	bool mIsAlive = false;
	
	
	virtual void bulletUpdate(float dt);
public:
	CREATE_FUNC(CBullet);
	virtual bool init() override;
	virtual void update(float dt) override;

	void setSprite(Sprite * tSprite);
	bool isScreenOut(Vec2 tPos);
	void setDirection(Vec2 tDir);
	void setSpeed(float tSpeed);
	Sprite * getSprite() const;

	virtual bool getIsAlive();
	virtual void setIsAlive(bool tIsAlive);
	virtual void shot(Vec2 tPos);
	virtual void setColor(const Color3B & tColor);
	virtual void checkCollisionEnemy(CEnemy * enemy);
	virtual void checkCollisionActor(CActor * actor);

};

#endif // !__CBULLET_H__
