#ifndef __CACTOR_H__
#define __CACTOR_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CBulletDirection.h"

using namespace cocos2d;

class CActor : public CUnit
{
private:
	float mBulletInterval = 0;
	float mLatestShotTime = 0;

	int mCurrentBulletIndex = 0;
	Vector<CBulletDirection *> mBullets;
	Layer * mBulletLayer = nullptr;
public:
	virtual ~CActor();

	CREATE_FUNC(CActor);
	virtual bool lateInit() override;
	static CActor * create(Layer * tBulletLayer);
	virtual void update(float dt) override;

	//Inputs
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);
	
};

#endif // !__CACTOR_H__
