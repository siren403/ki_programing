#ifndef __CACTOR_H__
#define __CACTOR_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CBullet.h"

using namespace cocos2d;

class SpriteAnimator;

class CActor : public CUnit
{
private:
	SpriteAnimator * mSpriteAnim = nullptr;

	float mBulletInterval = 0;
	float mLatestShotTime = 0;
	bool mIsControl = false;

	int mCurrentBulletIndex = 0;
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

	//Inputs
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);
};

#endif // !__CACTOR_H__
