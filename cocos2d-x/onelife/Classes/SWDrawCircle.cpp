#include "SWDrawCircle.h"

SWDrawCircle::SWDrawCircle()
{
	mSprite = Sprite::create("white256x256.jpg");
	mSprite->retain();
	InitShaderWithSprite("shader/circle.fsh", mSprite);

	this->SetCircleSize(0.5f);
	this->SetOutline(0);
	this->SetInline(0.01f);
}

SWDrawCircle::~SWDrawCircle()
{
	CC_SAFE_RELEASE_NULL(mSprite);
}

Sprite * SWDrawCircle::GetSprite()
{
	return mSprite;
}

// 0 ~ 1
void SWDrawCircle::SetCircleSize(float size)
{
	size = clampf(size, 0.0f, 1.0f);
	mGLState->setUniformFloat("u_size", size);
}
// 0 ~ 1
void SWDrawCircle::SetOutline(float size)
{
	size = clampf(size, 0.0f, 1.0f);
	mGLState->setUniformFloat("u_outline", size);
}
// 0 ~ 1
void SWDrawCircle::SetInline(float size)
{
	size = clampf(size, 0.0f, 1.0f);
	mGLState->setUniformFloat("u_inline", size);
}
