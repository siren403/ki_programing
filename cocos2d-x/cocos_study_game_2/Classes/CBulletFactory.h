#ifndef __CBULLETFACTORY_H__
#define __CBULLETFACTORY_H__

#include "cocos2d.h"

using namespace cocos2d;

class CBullet;

struct DirSpeed
{
public:
	DirSpeed(Vec2 dir,float speed)
	{
		mDir = dir;
		mSpeed = speed;
	};
	Vec2 mDir;
	float mSpeed;
};

class CBulletFactory
{
public:
	static CBullet * creataBullet3Way(DirSpeed tLeft, DirSpeed tCenter, DirSpeed tRight);
};

#endif // !__CBULLETFACTORY_H__
