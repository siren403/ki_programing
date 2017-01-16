#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
class Mole;

class ScenePlay : public LayerColor
{
private:
	std::vector<Mole *> mMoles;
	int mCurrentScore = 0;
	float mCurrentTime = 0;
	Label * mLabelScore = nullptr;
	Sprite * mSpriteTime = nullptr;

	bool mIsUpdate = false;
public:
	static Scene * createScene();

	CREATE_FUNC(ScenePlay);

	virtual bool init() override;
	
	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch * touch, Event * event) override;

	void GameEnd();
};

#endif