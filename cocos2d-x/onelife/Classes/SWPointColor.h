#ifndef __SWPOINTCOLOR_H__
#define __SWPOINTCOLOR_H__

#include "ShaderWrapper.h"

class SWPointColor : public ShaderWrapper
{
public:
	SWPointColor(Sprite * targetSprite);

	void SetPointColor(const Vec3& color);
	void SetChangeColor(const Vec3& color);
	void SetColorRatio(const float& ratio);
};

#endif // !__SWPOINTCOLOR_H__
