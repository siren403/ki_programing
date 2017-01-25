#include "b2Util.h"

#define PTM_RATIO 32
#define DESTROY_TAG -1

int b2Util::mRatio = PTM_RATIO;
int b2Util::mDestroyTag = DESTROY_TAG;

b2Vec2 b2Util::ConvertTob2Vec(Vec2 vec)
{
	return b2Vec2(vec.x / mRatio, vec.y / mRatio);
}
b2Vec2 b2Util::ConvertTob2Vec(float x, float y)
{
	return ConvertTob2Vec(Vec2(x, y));
}

Vec2 b2Util::ConvertToVec(b2Vec2 vec)
{
	return Vec2(vec.x * mRatio, vec.y * mRatio);
}

int b2Util::GetRatio()
{
	return mRatio;
}

int b2Util::GetDestroyTag()
{
	return mDestroyTag;
}
