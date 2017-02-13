#include "BossHand.h"

#define PI 3.14159



bool BossHand::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("samples/boss_1_lefthand.png"));
	sprite->getTexture()->setAliasTexParameters();
	mHandDir = HandDir::HandDir_Left;

	this->scheduleUpdate();

	return true;
}

void BossHand::InitHand(HandDir dir)
{
	mHandDir = dir;
	GetSprite()->setFlipX(mHandDir == HandDir::HandDir_Left ? false : true);
}

void BossHand::OnAttack(Vec2 localPos)
{
	mState = State::Attack;
	mAttackTargetPos = localPos;
}

void BossHand::onEnter()
{
	EnemyParts::onEnter();
	mInitPos = this->getPosition();
}

void BossHand::update(float dt)
{
	switch (mState)
	{
	case State::Idle:
		UpdateIdle(dt);
		break;
	case State::Attack:
		UpdateAttack(dt);
		break;
	}
	
}

void BossHand::UpdateIdle(float dt)
{
	Vec2 pos = mInitPos;
	mIdleRadian += (PI * dt) * -1;
	if (mIdleRadian <= PI * -2)
	{
		mIdleRadian = 0;
	}
	pos.x += (cos(mIdleRadian) * 10) * mHandDir;
	pos.y += sin(mIdleRadian) * 10;
	this->setPosition(pos);
}

void BossHand::UpdateAttack(float dt)
{
	static bool isReturn = false;
	if (isReturn == false)
	{
		Vec2 pos = ccpLerp(this->getPosition(), mAttackTargetPos, dt);
		this->setPosition(pos);
		if (this->getPosition().getDistance(mAttackTargetPos) < 20)
		{
			isReturn = true;
		}
	}
	else
	{
		Vec2 pos = ccpLerp(this->getPosition(), mInitPos, dt);
		this->setPosition(pos);
		if (mInitPos.getDistance(this->getPosition()) < 5)
		{
			this->setPosition(mInitPos);
			mState = State::Idle;
		}
	}

}
