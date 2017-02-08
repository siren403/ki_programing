#include "BossHead.h"

bool BossHead::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_head.png"), 1);
	sprite->getTexture()->setAliasTexParameters();

	float headDuration = 1.5;
	auto tIdleSeq = Sequence::create(
		MoveBy::create(headDuration * 0.5,Vec2(0,5)),
		MoveBy::create(headDuration * 0.5, Vec2(0,-5)),
		nullptr
	);
	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
	this->runAction(tRepeatIdle);

	return true;
}

void BossHead::update(float dt)
{
}

const Size BossHead::GetPartsSize()
{
	return this->GetSprite()->getContentSize();
}
