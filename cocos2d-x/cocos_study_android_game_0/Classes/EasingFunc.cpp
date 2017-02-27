#include "EasingFunc.h"

#define PI 3.14159

float EasingFunc::Ease(const EasingData & data)
{
	float result;

	switch (data.type)
	{
	case EasingType::Ease_Linear:
		result = EasingFunc::EaseLinear(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_QuarticIn:
		result = EasingFunc::EaseQuarticIn(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_ExpoIn:
		result = EasingFunc::EaseExpoIn(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_ExpoOut:
		result = EasingFunc::EaseExpoOut(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_ExpoInOut:
		result = EasingFunc::EaseExpoInOut(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_SinInOut:
		result = EasingFunc::EaseSinInOut(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	case EasingType::Ease_QuadInOut:
		result = EasingFunc::EaseQuadInOut(data.currentTime, data.startValue, data.changeValue, data.duration);
		break;
	}

	return result;
}

/*
t = curTime : 누적시간.
b = startValue : 시작값.
c = changeValue : 시작값으로부터의 변화값. ex) startValue : 10, changeValue : 10 -> 10 ~ 20 
d = duration
*/
float EasingFunc::EaseLinear(float curTime, float startValue, float changeValue, float duration)
{
	return changeValue*curTime / duration + startValue;
}


//quadratic easing in / out - acceleration until halfway, then deceleration
//	Math.easeInOutQuad = function(t, b, c, d) {
//	t /= d / 2;
//	if (t < 1) return c / 2 * t*t + b;
//	t--;
//	return -c / 2 * (t*(t - 2) - 1) + b;
//};
float EasingFunc::EaseQuadInOut(float curTime, float startValue, float changeValue, float duration)
{
	curTime /= duration / 2;
	if (curTime < 1) 
		return changeValue / 2 * curTime*curTime + startValue;
	
	curTime--;
	return -changeValue / 2 * (curTime*(curTime - 2) - 1) + startValue;
}

float EasingFunc::EaseQuarticIn(float curTime, float startValue, float changeValue, float duration)
{
	curTime /= duration;
	return changeValue*curTime*curTime*curTime*curTime + startValue;
}

float EasingFunc::EaseExpoIn(float curTime, float startValue, float changeValue, float duration)
{
	return changeValue * pow(2, 10 * (curTime / duration-1)) + startValue;
}

float EasingFunc::EaseExpoOut(float curTime, float startValue, float changeValue, float duration)
{
	return changeValue * (-pow(2, -10 * curTime / duration) + 1) + startValue;
}

float EasingFunc::EaseExpoInOut(float curTime, float startValue, float changeValue, float duration)
{
	curTime /= duration / 2;
	if (curTime < 1)
	{
		return changeValue / 2 * pow(2, 10 * (curTime - 1)) + startValue;
	}
	curTime--;
	return changeValue / 2 * (-pow(2, -10 * curTime) + 2) + startValue;
}






float EasingFunc::EaseSinInOut(float curTime, float startValue, float changeValue, float duration)
{
	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}

Vec2 EasingFunc::EaseSinInOut(float curTime, Vec2 startValue, Vec2 changeValue, float duration)
{
	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}
