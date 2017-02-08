#include "BossHand.h"

bool BossHand::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_lefthand.png"));
	mHandDir = HandDir::HandDir_Left;

	return true;
}

void BossHand::update(float dt)
{

}

void BossHand::InitHand(HandDir dir)
{
	mHandDir = dir;
	GetSprite()->setFlipX(mHandDir == HandDir::HandDir_Left ? false : true);
}
