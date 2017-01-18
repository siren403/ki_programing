#ifndef __CUNIT_H__
#define __CUNIT_H__

#include "cocos2d.h"

using namespace cocos2d;

class CUnit : public Node
{
protected:
	Sprite * mSprite = nullptr;

public:
	virtual bool init() override;
	virtual bool lateInit();


	CREATE_FUNC(CUnit);
};

#endif // !__CUNIT_H__
