#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "cocos2d.h"

USING_NS_CC;

class SceneTitle : public LayerColor
{

private:
	ParallaxNode * mpParall = nullptr;
public:
	static Scene * createScene();
	
	CREATE_FUNC(SceneTitle);

	virtual bool init() override;
};


#endif