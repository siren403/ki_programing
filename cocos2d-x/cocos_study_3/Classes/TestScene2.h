#ifndef __SCENETRANS2_H__
#define __SCENETRANS2_H__

#include "cocos2d.h"

USING_NS_CC;

class TestScene2 : public LayerColor
{
public:
	static Scene * createScene();
	virtual bool init() override;

	CREATE_FUNC(TestScene2);

	void doClose(Ref * pSender);
};


#endif // !__SCENETRANS_H__
