#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Actor.h"

USING_NS_CC;


class Player : public Actor
{

public:
	Player();
	virtual ~Player();

	static Player * create();
	virtual bool init() override;

};

#endif // !__PLAYER_H__
