#include "BossHead.h"

bool BossHead::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	mSprite = Sprite::create("samples/boss_1_head.png");
	this->addChild(mSprite, 1);

	return true;
}

void BossHead::update(float dt)
{
}

const Size BossHead::GetPartsSize()
{
	return mSprite->getContentSize();
}
