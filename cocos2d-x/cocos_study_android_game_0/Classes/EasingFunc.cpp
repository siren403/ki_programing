#include "EasingFunc.h"

#define PI 3.14159

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

float EasingFunc::EaseQuarticIn(float curTime, float startValue, float changeValue, float duration)
{
	curTime /= duration;
	return changeValue*curTime*curTime*curTime*curTime + startValue;
}






float EasingFunc::EaseSinInOut(float curTime, float startValue, float changeValue, float duration)
{
	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}

Vec2 EasingFunc::EaseSinInOut(float curTime, Vec2 startValue, Vec2 changeValue, float duration)
{
	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}
