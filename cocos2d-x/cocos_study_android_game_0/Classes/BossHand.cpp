#include "BossHand.h"

#define PI 3.14159


bool BossHand::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_lefthand.png"));
	sprite->getTexture()->setAliasTexParameters();
	mHandDir = HandDir::HandDir_Left;

	this->scheduleUpdate();

	return true;
}

void BossHand::InitHand(HandDir dir)
{
	mHandDir = dir;
	GetSprite()->setFlipX(mHandDir == HandDir::HandDir_Left ? false : true);
}

void BossHand::onEnter()
{
	EnemyParts::onEnter();
	mInitPos = this->getPosition();
}

void BossHand::update(float dt)
{
	Vec2 pos = mInitPos;
	mIdleRadian += (PI * dt) * -1;
	if (mIdleRadian <= PI * -2)
	{
		mIdleRadian = 0;
	}
	pos.x += (cos(mIdleRadian) * 10) * mHandDir;
	pos.y += sin(mIdleRadian) * 10;
	this->setPosition(pos);
}
