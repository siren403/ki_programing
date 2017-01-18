#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"

USING_NS_CC;

class ScenePlay : public Layer 
{

public:
	static Scene * createScene();
	CREATE_FUNC(ScenePlay);

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
};


#endif // !__SCENEPLAY_H__
