#include "BossParts.h"
#include "EasingFunc.h"

#define PI 3.14159

#pragma region Head

bool BossHead::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_head.png"), 1);
	sprite->getTexture()->setAliasTexParameters();

	float headDuration = 1.5;
	auto tIdleSeq = Sequence::create(
		MoveBy::create(headDuration * 0.5, Vec2(0, 5)),
		MoveBy::create(headDuration * 0.5, Vec2(0, -5)),
		nullptr
	);
	auto tRepeatIdle = RepeatForever::create(tIdleSeq);
	mHeadAction = this->runAction(tRepeatIdle);

	return true;
}
const Size BossHead::GetPartsSize()
{
	return this->GetSprite()->getContentSize();
}

#pragma endregion

#pragma region Body

bool BossBody::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_body.png"), 1);
	sprite->getTexture()->setAliasTexParameters();

	return true;
}
const Size BossBody::GetPartsSize()
{
	return GetSprite()->getContentSize();
}

#pragma endregion

#pragma region Hand

bool BossHand::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_lefthand.png"));
	sprite->getTexture()->setAliasTexParameters();
	mHandDirection = HandDir::HandDir_Left;


	this->scheduleUpdate();
	return true;
}
void BossHand::InitHand(HandDir dir)
{
	mHandDirection = dir;
	GetSprite()->setFlipX(mHandDirection == HandDir::HandDir_Left ? false : true);
}
Vec2 BossHand::GetInitPosition()
{
	return mInitPosition;
}

char BossHand::GetHandDirection()
{
	return mHandDirection;
}

void BossHand::SetAttackDuration(float duration)
{
	mAttackDuration = duration;
}

void BossHand::update(float dt)
{
	switch (mState)
	{
	case BossHand::State::Idle:
		UpdateIdle(dt);
		break;
	case BossHand::State::Attack_Shot:
		UpdateAttack(dt);
		break;
	}
}

void BossHand::OnAttack(Vec2 pos)
{
	mAttackTargetPos = pos;
	mState = State::Attack_Shot;
}
void BossHand::UpdateIdle(float dt)
{
	Vec2 pos;

	pos = mInitPosition;
	mIdleRadian += (PI * dt) * -1;
	if (mIdleRadian <= PI * -2)
	{
		mIdleRadian = 0;
	}
	pos.x += (cos(mIdleRadian) * 10) * mHandDirection;
	pos.y += sin(mIdleRadian) * 10;
	this->setPosition(pos);
}
void BossHand::UpdateAttack(float dt)
{
	mCurrentTime += dt;

	Vec2 pos;
	pos = EasingFunc::EaseSinInOut(sin(PI * mCurrentTime) *mAttackDuration, mInitPosition, mAttackTargetPos - mInitPosition, mAttackDuration);
	this->setPosition(pos);

	if (mCurrentTime >= 1)
	{
		mCurrentTime = 0;
		this->setPosition(mInitPosition);
		mState = State::Idle;
	}

}
void BossHand::onEnter()
{
	EnemyParts::onEnter();
	mInitPosition = this->getPosition();
}

#pragma endregion
