#include "EasingFunc.h"

#define PI 3.14159

/*
curTime : 누적시간.
startValue : 시작값.
changeValue : 시작값으로부터의 변화값. ex) startValue : 10, changeValue : 10 -> 10 ~ 20 
*/
float EasingFunc::EaseSinInOut(float curTime, float startValue, float changeValue, float duration)
{
	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}

Vec2 EasingFunc::EaseSinInOut(float curTime, Vec2 startValue, Vec2 changeValue, float duration)
{
	/*Vec2 pos;
	pos.x = -changeValue.x / 2 * (cos(PI * (curTime / duration)) - 1) + startValue.x;
	pos.y = -changeValue.y / 2 * (cos(PI * (curTime / duration)) - 1) + startValue.y;*/

	return -changeValue / 2 * (cos(PI * (curTime / duration)) - 1) + startValue;
}
