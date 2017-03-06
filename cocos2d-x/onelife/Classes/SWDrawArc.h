#ifndef __SWDRAWARC_H__
#define __SWDRAWARC_H__

#include "ShaderWrapper.h"

class SWDrawArc : public ShaderWrapper
{
public:
	SWDrawArc();
	virtual ~SWDrawArc();

	Sprite * GetSprite();
private:
	Sprite * mSprite = nullptr;
};

#endif // !__SWDRAWARC_H__
