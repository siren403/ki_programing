#ifndef __CUNIT_H__
#define __CUNIT_H__

#include "cocos2d.h"

using namespace cocos2d;

class CUnit : public Node
{
protected:
	//Sprite * mSprite = nullptr;
	virtual bool lateInit();
	bool mIsAlive = true;
public:
	CREATE_FUNC(CUnit);
	virtual bool init() override;
	virtual bool getIsAlive();
	virtual void setIsAlive(bool tIsAlive);
};

#endif // !__CUNIT_H__
