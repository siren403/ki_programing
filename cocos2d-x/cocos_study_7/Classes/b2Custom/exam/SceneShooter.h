#ifndef __SCENESHOOTER_H__
#define __SCENESHOOTER_H__

#include "b2Custom\b2Layer.h"

class SceneShooter : public b2Layer
{
private:
	Sprite * mpSpriteShooter = nullptr;
	float mTouchDistance = 0;
	float mShootDegree = 0;
public:
	static Scene * createScene();
	CREATE_FUNC(SceneShooter);

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

	void CalcShootDegree(Vec2 tTouchPos);
};

#endif // !__SCENESHOOTER_H__
