#include "Player.h"
#include "SpriteAnimator.h"
#include "CollisionUtils.h"
#include "EasingFunc.h"

//#define PI 3.14159

bool Player::init()
{
	if (!Actor::init())
	{
		return false;
	}

	mType = ActorType::Actor_Player;

	mSpriteAnim = SpriteAnimator::Create("actor", 0, 20, 0.1);
	mSpriteAnim->RunAni();
	mSpriteAnim->setScale(1.7 * CC_CONTENT_SCALE_FACTOR());
	mSpriteAnim->setPosition(Vec2(-mSpriteAnim->GetSprite()->getContentSize().width * 0.04, -mSpriteAnim->GetSprite()->getContentSize().height * 0.65));
	mSpriteAnim->GetSprite()->getTexture()->setAliasTexParameters();
	this->addChild(mSpriteAnim);

	mHP = 30;
	mMoveSpeedPower = 200;
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
		switch (mState)
		{
		case State::Roll:
			updateRoll(dt);
			
			break;
		case State::Move:
			updateMove(dt);
			break;
		}
		/*Vec2 pos = this->getPosition();
		pos.clamp(Vec2(mSpriteAnim->GetSprite()->getContentSize().width*0.5f, 
			mSpriteAnim->GetSprite()->getContentSize().width*0.5f), mMoveArea);

		this->setPosition(pos);*/
	}
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
	mMoveArea.width -= mSpriteAnim->GetSprite()->getContentSize().width* 0.5;
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
	}
	
}

void Player::OnCollisionOther(bool isCollision, Node * other, Vec2 normal)
{
	if (mIsAlive == false)
	{
		return;
	}

	if (isCollision)
	{
		Actor * actor = (Actor *)other;
		if (actor != nullptr)
		{
			Vec2 worldPos = this->getParent()->convertToWorldSpace(this->getPosition());
			Vec2 normal = CollisionUtils::GetInst()->GetPosToRectNormal(other, worldPos);
			switch (actor->GetActorType())
			{
			case ActorType::Actor_Tile:
				//log("normal : %f,%f", normal.x, normal.y);
				if (normal.x != 0)
				{
					mIsVerticalCollision = true;
				}
				if (normal.y != 0)
				{
					mIsHorizontalCollision = true;
				}
				break;
			case ActorType::Actor_EnemyParts:
				
				log("dead");
				mIsAlive = false;
				
				break;
			}
			
		}
	}
}

void Player::InitPosition(Vec2 pos)
{
	this->setPosition(pos);

	mMoveDir = Vec2::ZERO;
	mPrevPos = pos;
	mIsVerticalCollision = false;
	mIsHorizontalCollision = false;
	mRollCurTime = 0;
	mRollDestPos = pos;
	mState = State::Idle;
}

void Player::updateMove(float dt)
{
	Vec2 pos = this->getPosition();
	pos.x += (mMoveDir.x * mMoveSpeedPower) * dt;
	pos.y += (mMoveDir.y * mMoveSpeedPower) * dt;


	if (mIsVerticalCollision)
	{
		pos.x = mPrevPos.x;
		mIsVerticalCollision = false;
	}
	if (mIsHorizontalCollision)
	{
		pos.y = mPrevPos.y;
		mIsHorizontalCollision = false;
	}


	this->setPosition(pos);
	mPrevPos = this->getPosition();
}

void Player::updateRoll(float dt)
{

	mRollCurTime += dt;
	if (mRollCurTime >= mRollDuration)
	{
		mRollCurTime = 0;
		mState = State::Idle;
	}
	else
	{
		Vec2 pos = EasingFunc::EaseSinInOut(mRollCurTime,mRollStartPos,mRollDestPos - mRollStartPos,mRollDuration);

		if (mIsVerticalCollision)
		{
			pos.x = mPrevPos.x;
			mIsVerticalCollision = false;
			mRollCurTime = 0;
			mState = State::Idle;
		}
		if (mIsHorizontalCollision)
		{
			pos.y = mPrevPos.y;
			mIsHorizontalCollision = false;
			mRollCurTime = 0;
			mState = State::Idle;
		}

		this->setPosition(pos);
		mPrevPos = this->getPosition();

		//float start = 10;
		//float end = 20;
		//float delta = EasingFunc::EaseSinInOut(mRollCurTime, 10, 10, mRollDuration);
		//log("delta %f to %f : %f", start, end, delta);
	}

}

Player::~Player()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

