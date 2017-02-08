#include "BossHead.h"

bool BossHead::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_head.png"), 1);

	return true;
}

void BossHead::update(float dt)
{
}

const Size BossHead::GetPartsSize()
{
	return this->GetSprite()->getContentSize();
}
