#ifndef __B2UTIL_H__
#define __B2UTIL_H__

#include "Box2D\Box2D.h"
#include "cocos2d.h"


using namespace cocos2d;

class b2Util
{
private:
	static int mRatio;
	static int mDestroyTag;
public:
	static b2Vec2 ConvertTob2Vec(Vec2 vec);
	static b2Vec2 ConvertTob2Vec(float x, float y);
	static Vec2 ConvertToVec(b2Vec2 vec);

	static int GetRatio();
	static int GetDestroyTag();
};

#endif // !__B2UTIL_H__
