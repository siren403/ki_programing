#ifndef __EASINGFUNC_H__
#define __EASINGFUNC_H__

#include "cocos2d.h"

using namespace cocos2d;

class EasingFunc
{
public:
	static float EaseSinInOut(float curTime, float startValue, float changeValue, float duration);
	static Vec2 EaseSinInOut(float curTime, Vec2 startValue, Vec2 changeValue, float duration);

};

#endif // !__EASINGFUNC_H__
