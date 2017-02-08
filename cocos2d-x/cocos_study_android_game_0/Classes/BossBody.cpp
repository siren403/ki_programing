#include "BossBody.h"

bool BossBody::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	mSprite = Sprite::create("samples/boss_1_body.png");
	mSprite->getTexture()->setAliasTexParameters();
	this->addChild(mSprite, 1);


	return true;
}

void BossBody::update(float dt)
{

}

const Size BossBody::GetPartsSize()
{
	return mSprite->getContentSize();
}
