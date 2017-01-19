#include "CEnemyParts.h"


bool CEnemyParts::init()
{
	if (!CUnit::init())
	{
		return false;
	}

	mSprite = Sprite::create("boss_sample.png");
	this->addChild(mSprite);


	mHP = 100;
	mHitDelay = 0.08;

	this->scheduleUpdate();
	return true;
}

void CEnemyParts::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}
}

void CEnemyParts::setHP(int tHP)
{
	mHP = tHP;
}

Sprite * CEnemyParts::getSprite() const
{
	return mSprite;
}

void CEnemyParts::Hit()
{
	if (mCurrentHitDelay <= 0)
	{
		mHP--;
		log("parts hit count : %d", mHP);
		mCurrentHitDelay = mHitDelay;

		if (mHP <= 0)
		{
			setVisible(true);
		}

		if (this->isVisible())
		{
			auto tHitSeq = Sequence::create(
				TintTo::create(0.05, Color3B::RED),
				TintTo::create(0.05, Color3B::WHITE),
				nullptr
			);
			mSprite->runAction(tHitSeq);
		}

	}
}
