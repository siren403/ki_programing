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

	mMoveSpeed = 200;
	mMoveDir = Vec2::ZERO;
	mState = State::Idle;

	mRollRadian = 0;
	mRollDistance = 150;
	mRollDuration = 0.3;


	this->scheduleUpdate();
	return true;
}

void Player::update(float dt)
{

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

void Player::OnRoll(float rollRadian)
{
	if (mState == State::Move)
	{
		mState = State::Roll;
		mRollRadian = rollRadian;
		mRollStartPos = this->getPosition();
		mRollDestPos.x = mRollStartPos.x + (cos(rollRadian) * mRollDistance);
		mRollDestPos.y = mRollStartPos.y + (sin(rollRadian) * mRollDistance);

		mSpriteAnim->GetSprite()->stopAction(mRollColorAction);
		mRollColorAction = mSpriteAnim->GetSprite()->runAction(Sequence::create(
			TintTo::create(mRollDuration*0.75, Color3B(60,60,255)),
			TintTo::create(mRollDuration*0.25, Color3B::WHITE),
			nullptr));
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
				mSpriteAnim->GetSprite()->runAction(Sequence::create(
					TintTo::create(0.16,Color3B::RED),
					DelayTime::create(0.05),
					TintTo::create(0.16, Color3B::WHITE),
					nullptr));

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
	pos.x += (mMoveDir.x * mMoveSpeed) * dt;
	pos.y += (mMoveDir.y * mMoveSpeed) * dt;


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

		
	}

}

Player::~Player()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

