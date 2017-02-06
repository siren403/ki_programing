#ifndef __COLLISIONUTILS_H__
#define __COLLISIONUTILS_H__

#include "cocos2d.h"

using namespace cocos2d;


class CollisionUtils
{
public:
	static bool ContainsPointToPixel(Sprite * sprite, Image * image, Vec2 pos);
};

#endif // !__COLLISIONUTILS_H__
