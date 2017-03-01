#include "FakerParts.h"
#include "StopWatch.h"
#include "EasingFunc.h"
#include "DataManager.h"

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

#pragma region StopWatchs

	mMoveWatch = StopWatch::create();
	mMoveWatch->OnStart();
	this->addChild(mMoveWatch);
	mHideWatch = StopWatch::create();
	mHideWatch->OnStart();
	this->addChild(mHideWatch);

#pragma endregion
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
		UpdateMove(dt);
		UpdateHide(dt);
		break;
	}
}

void FakerSheep::UpdateIdle(float dt)
{

}

void FakerSheep::UpdateMove(float dt)
{
	mMoveWatch->OnUpdate(dt);

	mOriginPosition += (mMoveDirection * mMoveSpeed) * dt;

	Vec2 pos = mOriginPosition;
	pos.y += sin(PI * mMoveWatch->GetAccTime()) * mJumpHeight;
	
	if (mMoveWatch->GetAccTime() >= 1)
	{
		mMoveWatch->OnReset();
	}
	
	this->setPosition(pos);

}

void FakerSheep::UpdateHide(float dt)
{
	mHideWatch->OnUpdate(dt);

	float amount = EasingFunc::EaseQuarticIn(mHideWatch->GetAccTime(), 255, 0 - 255, mHideDuration);
	this->GetSprite()->setOpacity(amount);
	mFaceSprite->setOpacity(amount);

	if (mHideWatch->GetAccTime() >= mHideDuration)
	{
		OnHidePosition();
		SetSpriteAlpha(1);
		SetState(FakerSheep::State::State_Idle);
	}
}

void FakerSheep::SetSpriteAlpha(float alpha)
{
	this->GetSprite()->setOpacity(255 * alpha);
	mFaceSprite->setOpacity(255 * alpha);
}

void FakerSheep::SetState(FakerSheep::State state)
{
	mState = state;
	mMoveWatch->OnReset();
	mHideWatch->OnReset();
	SetSpriteAlpha(1);
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
	this->GetSprite()->setScaleX(mMoveDirection.x > 0 ? -1 : 1);

}

void FakerSheep::SetMoveSpeed(float speed)
{
	mMoveSpeed = speed;
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


