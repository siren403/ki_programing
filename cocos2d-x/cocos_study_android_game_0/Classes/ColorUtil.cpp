#include "ColorUtil.h"

Vec3 ColorUtil::Convert255ToOne(float r, float g, float b)
{
	return Vec3(r / 255, g / 255, b / 255);
}
