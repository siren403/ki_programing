#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

USING_NS_CC;

class Actor : public Node 
{
protected:
	int mMaxHp = 0;
	int mCurHp = 0;

	Sprite * mpActorSprite = nullptr;

public:
	Actor();
	virtual ~Actor();

	static Actor * create();
	static Actor * create(int tHp);

	virtual bool init() override;

	void SetSprite(Sprite * tpSprite);
	Sprite * GetSprite();

	void initHp(int tHp);
};

#endif // !__ACTOR_H__
