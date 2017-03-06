#ifndef __EFFECTENEMYKILL_H__
#define __EFFECTENEMYKILL_H__

#include "cocos2d.h"

using namespace cocos2d;

class EffectEnemyKill : public Node
{
public:
	CREATE_FUNC(EffectEnemyKill);
	virtual bool init() override;

	FiniteTimeAction * CreateAction(Vec2 playerPos,Vec2 enemyPos);
	void Show(Vec2 playerPos, Vec2 enemyPos);
private:
	Vec2 mLineAnchor;
	Color3B mLineColor;
	Rect mLineRect;
	float mLineAngle;

	Sprite * mLine_0 = nullptr;
	Sprite * mLine_1 = nullptr;
};

#endif // !__EFFECTENEMYKILL_H__
