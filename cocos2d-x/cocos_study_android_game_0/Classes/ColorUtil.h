#ifndef __COLORUTIL_H__
#define __COLORUTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

class ColorUtil
{
public:
	static Vec3 Convert255ToOne(float r, float g, float b);

};

#endif // !__COLORUTIL_H__
