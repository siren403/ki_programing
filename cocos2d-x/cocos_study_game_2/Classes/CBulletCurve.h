#ifndef __CBULLETCURVE_H__
#define __CBULLETCURVE_H__

#include "cocos2d.h"
#include "CBullet.h"

using namespace cocos2d;

class CBulletCurve : public CBullet
{
protected:
	float mRadius = 0;
	float mAccumulateTime = 0;
	virtual void bulletUpdate(float dt) override;
public:
	CREATE_FUNC(CBulletCurve);
	void setRadius(float tRadius);

	virtual void shot(Vec2 tPos) override;
};


#endif // !__CBULLETCURVE_H__
