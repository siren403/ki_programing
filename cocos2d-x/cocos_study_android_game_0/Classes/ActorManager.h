#ifndef __ACTORMANAGER_H__
#define __ACTORMANAGER_H__

#include "cocos2d.h"

class Actor;
class Player;

class ActorManager
{
private:
	static ActorManager * mInstance;
	ActorManager();
	~ActorManager();
public:
	static ActorManager * GetInstance();


private:
	Player * mPlayer = nullptr;
public:
	void SetPlayer(Player * player);
	Player * GetPlayer();

};

#endif // !__ACTORMANAGER_H__
