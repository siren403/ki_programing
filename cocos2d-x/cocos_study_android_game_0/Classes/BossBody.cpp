#include "BossBody.h"

bool BossBody::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_body.png"), 1);

	return true;
}

void BossBody::update(float dt)
{

}

const Size BossBody::GetPartsSize()
{
	return GetSprite()->getContentSize();
}
