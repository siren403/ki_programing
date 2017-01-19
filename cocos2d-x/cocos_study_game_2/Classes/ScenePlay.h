#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"

using namespace cocos2d;

class CActor;
class CEnemy;


class ScenePlay : public LayerColor 
{
private:
	CActor * mActor = nullptr;
	CEnemy * mEnemy = nullptr;
public:
	static Scene * createScene();
	CREATE_FUNC(ScenePlay);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

};


#endif // !__SCENEPLAY_H__
