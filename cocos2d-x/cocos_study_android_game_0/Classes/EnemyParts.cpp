#include "EnemyParts.h"
#include "Enemy.h"



bool EnemyParts::init()
{
	if (!Actor::init())
	{
		return false;
	}

	mType = ActorType::Actor_EnemyParts;


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

Sprite * EnemyParts::GetSprite()
{
	if (mSprite == nullptr)
	{
		mSprite = Sprite::create("CloseNormal.png");
		mSprite->setScale(0.5);
		this->addChild(mSprite);
	}
	return mSprite;
}
Sprite *  EnemyParts::SetSprite(Sprite * sprite, int localZOrder)
{
	if (mSprite != nullptr)
	{
		this->removeChild(mSprite);
	}
	mSprite = sprite;
	this->addChild(mSprite, localZOrder);

	return mSprite;
}
void EnemyParts::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}

const Size EnemyParts::GetPartsSize()
{
	//log("override EnemyParts::GetPartsSize()!!");
	if (mSprite != nullptr)
	{
		return mSprite->getContentSize();
	}
	return Size::ZERO;
}
