#ifndef __EASINGFUNC_H__
#define __EASINGFUNC_H__

#include "cocos2d.h"

using namespace cocos2d;

enum EasingType
{
	Ease_Linear = 0,
	Ease_QuarticIn = 1,
	Ease_ExpoIn = 2,
	Ease_ExpoOut = 3,
	Ease_ExpoInOut = 4,
	Ease_SinInOut = 5,
	Ease_QuadInOut = 6,
};

struct EasingData
{
	EasingType type;
	float currentTime;
	float startValue;
	float changeValue;
	float duration;

	EasingData()
	{

	}
	EasingData(EasingType type,float curTime,float startValue,float changeValue,float duration)
		: type(type),currentTime(curTime),startValue(startValue),changeValue(changeValue),duration(duration)
	{

	}
};


class EasingFunc
{
public:
	static float Ease(const EasingData & data);
	
	
	//Linear
	static float EaseLinear(float curTime, float startValue, float changeValue, float duration);


	
	//Quadratic
	static float EaseQuadInOut(float curTime, float startValue, float changeValue, float duration);


	//Quartic
	static float EaseQuarticIn(float curTime, float startValue, float changeValue, float duration);

	//Exponential
	static float EaseExpoIn(float curTime, float startValue, float changeValue, float duration);
	static float EaseExpoOut(float curTime, float startValue, float changeValue, float duration);
	static float EaseExpoInOut(float curTime, float startValue, float changeValue, float duration);


	static float EaseSinInOut(float curTime, float startValue, float changeValue, float duration);
	static Vec2 EaseSinInOut(float curTime, Vec2 startValue, Vec2 changeValue, float duration);

};

#endif // !__EASINGFUNC_H__
