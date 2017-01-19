#include "CEnemyParts.h"
#include "CEnemy.h"

bool CEnemyParts::init()
{
	if (!CUnit::init())
	{
		return false;
	}

	mBullets.reserve(10);
	mHP = 100;
	mHitDelay = 0.08;
	mBulletInterval = 1;

	mCurrentState = STATE_IDLE;

	this->scheduleUpdate();
	return true;
}

void CEnemyParts::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}
	
	switch (mCurrentState)
	{
	case STATE_IDLE:
		break;
	case STATE_ATTACK:
		mLatestShotTime += dt;
		if (mLatestShotTime >= mBulletInterval)
		{
			if (mBullets.at(mCurrentBulletIndex)->getIsAlive() == false)
			{
				//todo : 탄 발사 위치 조정

				Vec2 tPos = getParent()->convertToWorldSpace(this->getPosition());
				log("x:%f,y:%f", tPos.x, tPos.y);

				tPos += mShotOffset;
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
		break;
	}
	
}

void CEnemyParts::setHP(int tHP)
{
	mHP = tHP;
}

void CEnemyParts::setSprite(Sprite * tSprite)
{
	if (mSprite != nullptr)
	{
		this->removeChild(mSprite);
	}
	mSprite = tSprite;
	mSprite->setPosition(Vec2::ZERO);
	this->addChild(mSprite);
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
			setIsAlive(false);
			this->unscheduleUpdate();
			auto tParent = (CEnemy *)getParent();
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

void CEnemyParts::setState(int state)
{
	mCurrentState = state;
}

const Vector<CBullet*> & CEnemyParts::getBullets() const
{
	return mBullets;
}

void CEnemyParts::setIsAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
	mSprite->setOpacity(tIsAlive ? 1 : 255 * 0.5);
}
void CEnemyParts::setShotOffset(Vec2 tOffset)
{
	mShotOffset = tOffset;
}

void CEnemyParts::setShotInterval(float tInterval)
{
	mBulletInterval = tInterval;
}
