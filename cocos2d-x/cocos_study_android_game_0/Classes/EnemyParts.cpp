#include "EnemyParts.h"
#include "Enemy.h"

bool EnemyParts::init()
{
	if (!Actor::init())
	{
		return false;
	}

	return true;
}

void EnemyParts::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}

}

void EnemyParts::Hit()
{
	/*if (mCurrentHitDelay <= 0)
	{
		mHP--;
		log("parts hit count : %d", mHP);
		mCurrentHitDelay = mHitDelay;

		if (mHP <= 0)
		{
			SetAlive(false);
			this->unscheduleUpdate();
			auto tParent = (Enemy *)getParent();
			tParent->DestroyParts();
		}

		if (this->mIsAlive)
		{
			auto tHitSeq = Sequence::create(
				TintTo::create(0.05, Color3B::RED),
				TintTo::create(0.05, Color3B::WHITE),
				nullptr
			);
			mSprite->runAction(tHitSeq);
		}

	}*/
}
void EnemyParts::SetHP(int tHP)
{
	mHP = tHP;
}

void EnemyParts::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}

const Size EnemyParts::GetPartsSize()
{
	log("override EnemyParts::GetPartsSize()!!");
	return Size::ZERO;
}
