#ifndef __MOLE_H__
#define __MOLE_H__

#include "cocos2d.h"
#include <functional>

USING_NS_CC;

typedef std::function<void(float)> StateFunc;

class Mole : public Node
{
private:
	Sprite * mSprite = nullptr;

	
	void stateIdle();
	void stateHit();
	void stateHide();

	float mPrevTime = 0;

	bool mIsActive = false;
	bool mIsHitable = false;
	int mMoveY = 60;
	float mMoveDuration = 0.25f;
	Action * mCurrentAction = nullptr;

	Vec2 mLowerPos;
	Vec2 mUpperPos;
public:
	CREATE_FUNC(Mole);
	

	virtual bool init() override;

	void start();
	void stop();
	bool checkHit(Vec2 touchPos);
	float getRandomValue(float max);
};

#endif // !__MOLE_H__
