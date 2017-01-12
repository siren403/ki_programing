#ifndef __SCENETRANS3_H__
#define __SCENETRANS3_H__

#include "cocos2d.h"

USING_NS_CC;

class TestScene3 : public LayerColor
{
public:
	static Scene * createScene();
	virtual bool init() override;

	CREATE_FUNC(TestScene3);

	void doClose(Ref * pSender);
};

#endif // !__SCENETRANS_H__
