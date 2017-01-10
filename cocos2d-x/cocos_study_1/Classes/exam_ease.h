#ifndef __EXAM_EASE_SCENE_H__
#define __EXAM_EASE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ExamEase : public Layer
{
private:
	enum 
	{
		TYPE_EASE = 0,
		TYPE_ELASTIC = 1,
		TYPE_BOUNCE = 2,
		TYPE_SPEED = 3
	};

	unsigned int mType = 0;

	Action *mpMove = NULL;
	Action *mpEaseIn = NULL;
	Action *mpEaseOut = NULL;
	Action *mpEaseInOut_1 = NULL;

private:
	Sprite *mpBall_0 = NULL;
	Sprite *mpBall_1 = NULL;
	Sprite *mpBall_2 = NULL;
	Sprite *mpBall_3 = NULL;

	void DoAction(Ref *pSender);
	void DoActionReset();

public:
	static Scene * createScene();

	virtual bool Init();

	void menuCloseCallback(Ref * pSender);

	CREATE_FUNC(ExamEase);
};


#endif // !__EXAM_EASE_SCENE_H__
