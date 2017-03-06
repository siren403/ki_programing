#include "SWDrawArc.h"

SWDrawArc::SWDrawArc()
{
	mSprite = Sprite::create("white256x256.jpg");
	mSprite->retain();
	InitShaderWithSprite("shader/arc.fsh", mSprite);
}

SWDrawArc::~SWDrawArc()
{
	CC_SAFE_RELEASE_NULL(mSprite);
}

Sprite * SWDrawArc::GetSprite()
{
	return mSprite;
}
