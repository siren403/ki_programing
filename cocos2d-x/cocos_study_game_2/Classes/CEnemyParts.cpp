#include "CEnemyParts.h"


bool CEnemyParts::init()
{
	if (!CUnit::init())
	{
		return false;
	}

	mSprite = Sprite::create("boss_sample.png");
	this->addChild(mSprite);

	mBullets.reserve(10);
	mHP = 100;
	mHitDelay = 0.08;
	mBulletInterval = 1;

	this->scheduleUpdate();
	return true;
}

void CEnemyParts::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}
	
	mLatestShotTime += dt;
	if (mLatestShotTime >= mBulletInterval)
	{
		if (mBullets.at(mCurrentBulletIndex)->getIsAlive() == false)
		{
			Vec2 tPos = this->getPosition();
			tPos = convertToWorldSpace(tPos);
			//tPos.x += mSpriteAnim->getContentSize().width;
			//tPos.y += mSpriteAnim->getContentSize().height * 0.5;

			mBullets.at(mCurrentBulletIndex)->shot(tPos);
			mCurrentBulletIndex++;
			if (mCurrentBulletIndex >= mBullets.size())
			{
				mCurrentBulletIndex = 0;
			}
		}
		mLatestShotTime = 0;
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

void CEnemyParts::addBullet(CBullet * tBullet)
{
	mBullets.pushBack(tBullet);
	mBulletLayer->addChild(tBullet);
}

void CEnemyParts::setBulletLayer(Layer * tBulletLayer)
{
	mBulletLayer = tBulletLayer;
}

const Vector<CBullet*> & CEnemyParts::getBullets() const
{
	return mBullets;
}
