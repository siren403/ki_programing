#include "IntUtils.h"

int IntUtils::ClampI(int value, int min, int max)
{
	return value < min ? min : value>max ? max : value;
}

float IntUtils::Dot(const Vec2I & a, const Vec2I & b)
{
	return a.x * b.x + a.y * b.y;
}
