#ifndef __SCENEGAMEOVER_H__
#define __SCENEGAMEOVER_H__

#include "cocos2d.h"

USING_NS_CC;

class SceneGameOver : public LayerColor
{
protected:
	void NextScene();
public:
	static Scene * createScene();

	virtual bool init() override;

	CREATE_FUNC(SceneGameOver);
};

#endif // !__SCENEGAMEOVER_H__
