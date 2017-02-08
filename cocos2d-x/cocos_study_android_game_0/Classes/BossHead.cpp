#include "BossHead.h"

bool BossHead::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	mSprite = Sprite::create("samples/boss_1_bighead.png");
	mSprite->getTexture()->setAliasTexParameters();
	this->addChild(mSprite, 1);

	auto tIdleSeq = Sequence::create(
		MoveBy::create(0.5,Vec2(0,5)),
		MoveBy::create(0.5, Vec2(0,-5)),
		nullptr
	);
	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
	mSprite->runAction(tRepeatIdle);

	return true;
}

void BossHead::update(float dt)
{
}

const Size BossHead::GetPartsSize()
{
	return mSprite->getContentSize();
}
