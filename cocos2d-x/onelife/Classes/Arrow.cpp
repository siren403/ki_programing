#include "Arrow.h"
#include "Player.h"
#include "CollisionUtils.h"
#include "SimpleAudioEngine.h"
#include "ShaderWrapper.h"

using namespace CocosDenshion;

#define PI 3.14159
#define EPSILON 10
#define AUTO_RETURN false

bool Arrow::init()
{
	if (!Actor::init())
	{
		return false;
	}
	mType = ActorType::Actor_Arrow;

	mSprite = Sprite::create("samples/arrow_laser.png");
	mSprite->setScale(0.3f * CC_CONTENT_SCALE_FACTOR());
	mSprite->getTexture()->setAliasTexParameters();
	this->addChild(mSprite);

	mLaserShader = new ShaderWrapper("shader/arrow_laser.fsh", mSprite);
	/*this->runAction(RepeatForever::create(ActionFloat::create(1, 0.6f, 0.65f, [this](float value) 
	{
		mLaserShader->SetFloat("u_laserFactor", value);
	})));*/
	mLaserShader->SetFloat("u_laserFactor", 0.85f);
	mSprite->runAction(RepeatForever::create(Sequence::create(
		TintTo::create(1, Color3B(0, 255,0)),
		TintTo::create(1, Color3B(0, 255,0)),
		nullptr)));


	SimpleAudioEngine::getInstance()->preloadEffect("sound/bow_fire.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/pop_clip_in.mp3");

	SetState(State::State_Idle);
	mMaxSpeedPower = 2000;
	mDecelRatio = 0.05;

	this->scheduleUpdate();
	return true;
}

void Arrow::update(float dt)
{
	switch (mState)
	{
	case State::State_Idle:
	case State::State_LockOn:
		UpdateLock(dt);
		break;
	case State::State_Shot:
		UpdateShot(dt);
		break;
	case State::State_Drop:
		UpdateDrop(dt);
		break;
	}
	//log(mIsCollision ? "isColl true" : "is Coll false");
}

Arrow::State Arrow::GetState()
{
	return this->mState;
}

Vec2 Arrow::GetMoveDirection()
{
	return mMoveDirection;
}

void Arrow::InitWithPlayer(Player * player)
{
	mPlayer = player;
}


void Arrow::LockOn(Vec2 dir, bool isIgnoreState)
{
	if (isIgnoreState == false)
	{
		if (mState == State::State_Idle || mState == State::State_LockOn)
		{
			mMoveDirection = dir;
		}
	}
	else
	{
		//mState = State::State_LockOn;
		SetState(State::State_LockOn);
		mMoveDirection = dir;
	}

}

void Arrow::DisableLockOn()
{
	if (mState == State::State_LockOn)
	{
		//mState = State::State_Idle;
		SetState(State::State_Idle);
	}
	if (mState == State::State_Drop)
	{
		mIsReturnArrow = false;
	}
}


void Arrow::Shot()
{
	if (mState == State::State_Idle || mState == State::State_LockOn)
	{
		//mState = State::State_Shot;
		SetState(State::State_Shot);
		mCurrentSpeedPower = mMaxSpeedPower;
		SimpleAudioEngine::getInstance()->playEffect("sound/bow_fire.wav");
	}
}

void Arrow::OnCollisionOther(bool isCollision, Node * other,Vec2 normal)
{

	if (mState == State::State_Shot)
	{
		mIsCollision = isCollision;

		if (mIsCollision && !mIsPrevCollision)
		{
			if (other != nullptr)
			{
				Vec2 worldPos = this->getParent()->convertToWorldSpace(this->getPosition());
				Vec2 normal = CollisionUtils::GetInst()->GetPosToRectNormal(other, worldPos);
				//log("collision normal : %f,%f", normal.x, normal.y);

				Vec2 reflectDir;
				reflectDir = mMoveDirection + ((normal * 2)*ccpDot(-mMoveDirection, normal));
				mMoveDirection = reflectDir;
			}
			else//normal direct
			{
				mMoveDirection = normal;
			}

			float radian = atan2(mMoveDirection.y, mMoveDirection.x);
			this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + radian));
			mCurrentSpeedPower *= 0.6;
		}
		mIsPrevCollision = mIsCollision;
	}
	else
	{
		mIsPrevCollision = false;
	}

}


void Arrow::SetReturnArrow(bool isReturn)
{
	mIsReturnArrow = isReturn;
}

bool Arrow::IsShooting()
{
	return mState == State::State_Shot;
}

void Arrow::UpdateLock(float dt)
{
	Vec2 arrowPos;

	float radian = atan2(mMoveDirection.y, mMoveDirection.x);
	arrowPos.x = mPlayer->getPosition().x + cos(radian) * mPlayer->GetSprite()->getContentSize().width * 1.4f;
	arrowPos.y = mPlayer->getPosition().y + sin(radian) * mPlayer->GetSprite()->getContentSize().width * 1.4f;

	this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + radian));
	this->setPosition(arrowPos);
}

void Arrow::UpdateShot(float dt)
{
	/*static float time = 0;
	time += dt;
	if (time >= 1)
	{
		time = 0;
		mState = State::State_Drop;
	}*/

	//Vec2 dir = GetShotRadianToVector();
	//dir.x = cos(mShotRadian);
	//dir.y = sin(mShotRadian);
	//log("%f,%f,%f", mShotRadian,dir.x, dir.y);
	Vec2 pos = this->getPosition();
	pos.x += (mMoveDirection.x * mCurrentSpeedPower) * dt;
	pos.y += (mMoveDirection.y * mCurrentSpeedPower) * dt;

	this->setPosition(pos);
	mCurrentSpeedPower -= mCurrentSpeedPower * mDecelRatio;

	if (mCurrentSpeedPower <= EPSILON)
	{
		SetState(State::State_Drop);
		mCurrentSpeedPower = mMaxSpeedPower * 0.35;
	}
}

void Arrow::UpdateDrop(float dt)
{

#if AUTO_RETURN
#pragma region 자동회수

	//if (mPlayer->GetState() == Player::State::Move)
	//{
	//	Vec2 dist = mPlayer->getPosition() - this->getPosition();
	//	Vec2 pos = this->getPosition();

	//	pos.x += (dist.x * mCurrentSpeed) * dt;
	//	pos.y += (dist.y * mCurrentSpeed) * dt;
	//	this->setPosition(pos);

	//	if (dist.getLength() < 30)
	//	{
	//		mState = State_Idle;
	//	}
	//	//log("%f", dist.getLength());
	//}
	//Vec2 dir = this->getPosition() - mPlayer->getPosition();
	//dir.normalize();
	//float arrowRadian = atan2(dir.y, dir.x);
	//this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + arrowRadian));

	Vec2 dist;
	Vec2 dir;
	if (mPlayer->GetState() == Player::State::Move)
	{
		dist = mPlayer->getPosition() - this->getPosition();
		dir = dist.getNormalized();

		Vec2 pos = this->getPosition();
		pos.x += (dir.x * mCurrentSpeedPower) * dt;
		pos.y += (dir.y * mCurrentSpeedPower) * dt;
		this->setPosition(pos);

		if (dist.getLength() < 30)
		{
			//mState = State_Idle;
			SetState(State::State_Idle);
		}
		//log("%f", dist.getLength());
	}

	dist = this->getPosition() - mPlayer->getPosition();
	dir = dist.getNormalized();
	float arrowRadian = atan2(dir.y, dir.x);
	this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + arrowRadian));
#pragma endregion

#else // !AUTO_RETURN
#pragma region 수동회수
	if (mIsReturnArrow)
	{
		Vec2 dist;
		Vec2 dir;

		dist = mPlayer->getPosition() - this->getPosition();
		dir = dist.getNormalized();

		Vec2 pos = this->getPosition();
		pos.x += (dir.x * mCurrentSpeedPower) * dt;
		pos.y += (dir.y * mCurrentSpeedPower) * dt;
		this->setPosition(pos);

		if (dist.getLength() < 30)
		{
			//mState = State_Idle;
			SetState(State::State_Idle);
			SimpleAudioEngine::getInstance()->playEffect("sound/pop_clip_in.mp3");
		}
		//log("%f", dist.getLength());

		dist = this->getPosition() - mPlayer->getPosition();
		dir = dist.getNormalized();
		float arrowRadian = atan2(dir.y, dir.x);
		this->setRotation(-CC_RADIANS_TO_DEGREES((PI * 0.5) + arrowRadian));

	}
#pragma endregion
#endif // END AUTO_RETURN

}

void Arrow::SetState(Arrow::State state)
{
	mState = state;
	//mIsPrevCollision = false;
	//mIsCollision = false;
}
