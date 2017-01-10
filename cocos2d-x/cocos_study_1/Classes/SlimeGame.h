#ifndef __SLIMEGAME_SCENE_H__
#define __SLIMEGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class SlimeGame : public cocos2d::Layer
{
private:

public:
	static cocos2d::Scene * createScene();

	virtual bool Init();

	void menuCloseCallback(Ref *pSender);

	CREATE_FUNC(SlimeGame);

};

#endif // !__GAME_SCENE_H__
