#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"

USING_NS_CC;

class ScenePlay : public Layer 
{
public:
	static Scene * createScene();
	virtual bool init() override;
	CREATE_FUNC(ScenePlay);
};


#endif // !__SCENEPLAY_H__
