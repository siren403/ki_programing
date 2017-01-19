#ifndef __BULLETFACTORY_H__
#define __BULLETFACTORY_H__

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

class BulletFactory
{
public:
	static CBullet * creataBullet3Way(DirSpeed tLeft, DirSpeed tCenter, DirSpeed tRight);
};

#endif // !__BULLETFACTORY_H__
