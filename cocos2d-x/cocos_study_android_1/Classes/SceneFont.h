#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class SceneFont : public LayerColor
{
public:
	static Scene * createScene();
	CREATE_FUNC(SceneFont);
	virtual bool init() override;
};