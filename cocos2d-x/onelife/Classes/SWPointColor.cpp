#include "SWPointColor.h"
#include "ColorUtil.h"

SWPointColor::SWPointColor(Sprite * targetSprite)
{
	InitShaderWithSprite("shader/pointColor.fsh", targetSprite);
	SetPointColor(Vec3(1, 0, 1));
}

void SWPointColor::SetPointColor(const Vec3 & color)
{
	mGLState->setUniformVec3("pointColor", color);
}

void SWPointColor::SetChangeColor(const Vec3 & color)
{
	mGLState->setUniformVec3("changeColor", color);
}

void SWPointColor::SetColorRatio(const float & ratio)
{
	mGLState->setUniformFloat("colorRatio", ratio);
}

void SWPointColor::SetBaseColor(const Vec3 & color)
{
	mGLState->setUniformVec3("baseColor", color);
}
