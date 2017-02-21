#include "FakerParts.h"
#include "StopWatch.h"
#include "EasingFunc.h"

#define PI 3.14159

bool FakerSheep::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("enemy/sheep.png"));

	mFaceSprite = Sprite::create();
	mFaceSprite->setPosition(Vec2(38, 55));
	mFaceSprite->getTexture()->setAliasTexParameters();
	sprite->addChild(mFaceSprite);

	mStopWatch = StopWatch::create();
	mStopWatch->OnStart();
	this->addChild(mStopWatch);

	SetState(FakerSheep::State::State_Idle);
	mJumpHeight = 50;
	mHideDuration = 1;

	this->scheduleUpdate();
	return true;
}

void FakerSheep::update(float dt)
{
	switch (mState)
	{
	case FakerSheep::State::State_Idle:
		UpdateIdle(dt);
		break;
	case FakerSheep::State::State_DirMove:
		UpdateMove(dt);
		break;
	case FakerSheep::State::State_Hide:
		UpdateHide(dt);
		break;
	}
}

void FakerSheep::UpdateIdle(float dt)
{

}

void FakerSheep::UpdateMove(float dt)
{
	mStopWatch->OnUpdate(dt);

	mOriginPosition += (mMoveDirection * mMoveSpeedPower) * dt;

	Vec2 pos = mOriginPosition;
	pos.y += sin(PI * mStopWatch->GetAccTime()) * mJumpHeight;
	
	if (mStopWatch->GetAccTime() >= 1)
	{
		mStopWatch->OnReset();
	}
	
	this->setPosition(pos);
}

void FakerSheep::UpdateHide(float dt)
{
	mStopWatch->OnUpdate(dt);

	float amount = EasingFunc::EaseQuarticIn(mStopWatch->GetAccTime(), 255, 0 - 255, mHideDuration);
	this->GetSprite()->setOpacity(amount);
	mFaceSprite->setOpacity(amount);

	if (mStopWatch->GetAccTime() >= mHideDuration)
	{
		this->SetOriginPosition(Vec2(0, -100));
		this->GetSprite()->setOpacity(255);
		mFaceSprite->setOpacity(255);
		SetState(FakerSheep::State::State_Idle);
	}
}

void FakerSheep::SetState(FakerSheep::State state)
{
	mState = state;
	mStopWatch->OnReset();
}

void FakerSheep::SetFace(FaceType type)
{
	mFaceType = type;
	std::string faceName = StringUtils::format("enemy/sheep_face_%d.png", mFaceType);
	//log(faceName.c_str());
	mFaceSprite->setTexture(faceName);
	mFaceSprite->getTexture()->setAliasTexParameters();
}

void FakerSheep::SetMoveDirection(Vec2 dir)
{
	mMoveDirection = dir.getNormalized();
}

void FakerSheep::SetMoveDirection(float angle)
{
	float radian = CC_DEGREES_TO_RADIANS(angle);
	mMoveDirection.x = cos(radian);
	mMoveDirection.y = sin(radian);
	this->GetSprite()->setFlipX(mMoveDirection.x > 1 ? true : false);
}

void FakerSheep::SetMoveSpeedPower(float speedPower)
{
	mMoveSpeedPower = speedPower;
}

void FakerSheep::SetOriginPosition(Vec2 pos)
{
	mOriginPosition = pos;
	this->setPosition(mOriginPosition);
}

float FakerSheep::GetHideDuration()
{
	return mHideDuration;
}

void FakerSheep::OnHidePosition()
{
	this->SetOriginPosition(Vec2(0, -100));
}


