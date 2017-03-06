#ifndef __SWDRAWCIRCLE_H__
#define __SWDRAWCIRCLE_H__

#include "ShaderWrapper.h"


class SWDrawCircle : ShaderWrapper
{
public:
	SWDrawCircle();
	virtual ~SWDrawCircle();

	Sprite * GetSprite();

	void SetCircleSize(float size);
	void SetOutline(float size);
	void SetInline(float size);

private:
	Sprite * mSprite = nullptr;
};


#endif // !__SWDRAWCIRCLE_H__
