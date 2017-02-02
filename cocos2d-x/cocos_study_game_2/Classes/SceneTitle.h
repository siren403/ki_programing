#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "cocos2d.h"

USING_NS_CC;

#pragma execution_character_set("utf-8");

class SceneTitle : public Layer
{
public:
	static Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(SceneTitle);
};

#endif // !__SCENETITLE_H__
