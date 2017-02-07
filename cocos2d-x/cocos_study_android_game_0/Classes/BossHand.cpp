#include "BossHand.h"

bool BossHand::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	mSprite = Sprite::create("samples/boss_1_lefthand.png");
	this->addChild(mSprite);
	mHandDir = HandDir::HandDir_Left;


	return true;
}

void BossHand::update(float dt)
{

}

void BossHand::InitHand(HandDir dir)
{
	mHandDir = dir;
	mSprite->setFlipX(mHandDir == HandDir::HandDir_Left ? false : true);
}
