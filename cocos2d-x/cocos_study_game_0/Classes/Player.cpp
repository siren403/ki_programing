#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	this->removeAllChildren();
}

Player * Player::create()
{
	auto tpPlayer = new Player();
	if (tpPlayer->init())
	{
		tpPlayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(tpPlayer);
	}
	return tpPlayer;
}

bool Player::init()
{
	if (!Actor::init())
	{
		return false;
	}

	return true;
}
