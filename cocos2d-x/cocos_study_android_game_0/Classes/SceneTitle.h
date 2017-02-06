#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneTitle : public LayerColor
{
public:
	static Scene * createScene();
	CREATE_FUNC(SceneTitle);

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

};

#endif // !__SCENETITLE_H__
