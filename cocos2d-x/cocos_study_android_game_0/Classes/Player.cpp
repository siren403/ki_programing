#include "Player.h"
#include "SpriteAnimator.h"

#define PI 3.14159

bool Player::init()
{
	if (!Actor::init())
	{
		return false;
	}

	mSpriteAnim = SpriteAnimator::Create("actor", 0, 20, 0.1);
	mSpriteAnim->RunAni();
	mSpriteAnim->setScale(1.7 * CC_CONTENT_SCALE_FACTOR());
	mSpriteAnim->setPosition(Vec2(-mSpriteAnim->GetSprite()->getContentSize().width * 0.04, -mSpriteAnim->GetSprite()->getContentSize().height * 0.65));
	mSpriteAnim->GetSprite()->getTexture()->setAliasTexParameters();
	this->addChild(mSpriteAnim);

	mHP = 30;
	mMoveSpeedPower = 180;
	mMoveDir = Vec2::ZERO;
	mState = State::Idle;

	mRollRadian = 0;
	mRollDistance = 130;
	mRollDuration = 0.3;


	this->scheduleUpdate();
	return true;
}

void Player::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}

	if (mIsControl)
	{
		Vec2 pos = this->getPosition();

		switch (mState)
		{
		case State::Roll:
			mRollCurTime += dt;
			if (mRollCurTime >= mRollDuration)
			{
				mRollCurTime = 0;
				mState = State::Idle;
			}
			else
			{
				//pos.x = -mRollDestPos.x / 2 * (cos(PI*mRollCurTime / mRollDuration) - 1) + mRollStartPos.x;
				//pos.y = -mRollDestPos.y / 2 * (cos(PI*mRollCurTime / mRollDuration) - 1) + mRollStartPos.y;
				//pos = -mRollDestPos / 2 * (cos(PI*mRollCurTime / mRollDuration) - 1) + mRollStartPos;
				//log("%f,%f", this->getPosition().y, pos.y);
				
			}

			break;
		case State::Move:
			pos.x += (mMoveDir.x * mMoveSpeedPower) * dt;
			pos.y += (mMoveDir.y * mMoveSpeedPower) * dt;
			break;
		}

		//playNodeSize clamp
		//pos.clamp(Vec2(mSpriteAnim->GetSprite()->getContentSize().width*0.5f, 
		//	mSpriteAnim->GetSprite()->getContentSize().width*0.5f), mMoveArea);

		//pos.clamp(Vec2(0, 0), mMoveArea);
		this->setPosition(pos);
	}
	/*if (mMoveDir != Vec2::ZERO)
	{
		mMoveDir = Vec2::ZERO;
	}*/
}
Sprite * Player::GetSprite()
{
	return mSpriteAnim->GetSprite();
}
void Player::SetIsControl(bool tIsControl)
{
	mIsControl = tIsControl;
}

bool Player::GetIsControl()
{
	return mIsControl;
}
void Player::SetMoveDir(Vec2 dir)
{
	if (mState == State::Idle || mState == State::Move)
	{
		this->mMoveDir = dir;
		if (this->mMoveDir != Vec2::ZERO)
		{
			mState = State::Move;
		}
		else
		{
			mState = State::Idle;
		}
	}
}
Vec2 Player::GetMoveDir()
{
	return mMoveDir;
}
void Player::SetMoveArea(Size area)
{
	mMoveArea = area;
	mMoveArea.width -= mSpriteAnim->GetSprite()->getContentSize().width*0.5;
	mMoveArea.height -= mSpriteAnim->GetSprite()->getContentSize().height;
}
Player::State Player::GetState()
{
	return mState;
}
void Player::Hit()
{
	if (mCurrentHitDelay <= 0)
	{
		mHP--;
		log("parts hit count : %d", mHP);
		mCurrentHitDelay = mHitDelay;

		if (mHP <= 0)
		{
			mIsControl = false;
			mIsAlive = false;
		}

		if (mIsControl)
		{
			auto tHitSeq = Sequence::create(
				TintTo::create(0.05, Color3B::RED),
				TintTo::create(0.05, Color3B::WHITE),
				nullptr
			);
			mSpriteAnim->GetSprite()->runAction(tHitSeq);
		}
	}
}

void Player::OnRoll(float rollRadian)
{
	if (mState == State::Move)
	{
		mState = State::Roll;
		mRollRadian = rollRadian;
		mRollStartPos = this->getPosition();
		mRollDestPos.x = mRollStartPos.x + (cos(rollRadian) * mRollDistance);
		mRollDestPos.y = mRollStartPos.y + (sin(rollRadian) * mRollDistance);
		//log("start[%f,%f] dest[%f,%f]", mRollStartPos.x, mRollStartPos.y,mRollDestPos.x, mRollDestPos.y);
		auto roll = EaseSineInOut::create(
			MoveTo::create(mRollDuration, mRollDestPos)
		);
		this->runAction(roll);
	}
	
}

Player::~Player()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

bool Player::onTouchBegan(Touch * touch, Event * unused_event)
{

	return true;
}

void Player::onTouchMoved(Touch * touch, Event * unused_event)
{

}
