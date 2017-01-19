#ifndef __CENEMYPARTS_H__
#define __CENEMYPARTS_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CBullet.h"

using namespace cocos2d;

class CEnemyParts : public CUnit
{
private:
	Sprite * mSprite = nullptr;
	
	int mHP = 0;
	float mHitDelay = 0;
	float mCurrentHitDelay = 0;

	Layer * mBulletLayer = nullptr;

	Vector<CBullet *> mBullets;
	float mBulletInterval = 0;
	float mLatestShotTime = 0;
	int mCurrentBulletIndex = 0;
	Vec2 mShotOffset;

	int mCurrentState = 0;
public:
	CREATE_FUNC(CEnemyParts);
	virtual bool init() override;
	virtual void update(float dt) override;

	void setHP(int tHP);
	void setSprite(Sprite * tSprite);
	Sprite * getSprite() const;
	void Hit();
	void addBullet(CBullet * tBullet);
	void setBulletLayer(Layer * tBulletLayer);
	void setState(int state);
	void setShotOffset(Vec2 tOffset);
	void setShotInterval(float tInterval);
	const Vector<CBullet *> & getBullets() const;

	virtual void setIsAlive(bool tIsAlive) override;

	enum
	{
		STATE_IDLE = 0,
		STATE_ATTACK = 1,
	};
};


#endif // !__CENEMYPARTS_H__
