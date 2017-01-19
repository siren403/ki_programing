#ifndef __CACTOR_H__
#define __CACTOR_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CBullet.h"

using namespace cocos2d;

class SpriteAnimator;
class CEnemy;
class CBullet;

class CActor : public CUnit
{
private:
	SpriteAnimator * mSpriteAnim = nullptr;

	int mHP = 0;
	float mHitDelay = 0;
	float mCurrentHitDelay = 0;

	float mBulletInterval = 0;
	float mLatestShotTime = 0;
	int mCurrentBulletIndex = 0;

	bool mIsControl = false;
	float mFollowSpeed = 10.0f;
	Vec2 mLatestInputPos;

	Vector<CBullet *> mBullets;
	Layer * mBulletLayer = nullptr;
	virtual ~CActor();
public:
	static CActor * create(Layer * tBulletLayer);

	CREATE_FUNC(CActor);
	virtual bool lateInit() override;
	virtual void update(float dt) override;

	void setIsControl(bool tIsControl);
	bool getIsControl();
	void checkCollisionByEnemy(CEnemy * enemy);
	float getRedius();
	void hit();

	//Inputs
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);
	
};

#endif // !__CACTOR_H__
