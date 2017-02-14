#include "BossHand.h"
#include "EasingFunc.h"

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
	return mInitPosision;
}

char BossHand::GetHandDirection()
{
	return mHandDirection;
}

void BossHand::update(float dt)
{
	switch (mState)
	{
	case BossHand::Attack_Shot:
		UpdateAttack(dt);
		break;
	}
}

void BossHand::OnAttack(Vec2 pos)
{
	mAttackTargetPos = pos;
	mState = State::Attack_Shot;
}
void BossHand::UpdateAttack(float dt)
{
	mCurrentTime += dt;
	if (mCurrentTime > 2)
	{
		mCurrentTime = 0;
		this->setPosition(mInitPosision);
		mState = State::Idle;
	}

	Vec2 pos;
	pos = EasingFunc::EaseSinInOut(mCurrentTime, mInitPosision, mAttackTargetPos - mInitPosision, 2);
	this->setPosition(pos);

	//complete
	//mState = State::Idle;
}




void BossHand::onEnter()
{
	EnemyParts::onEnter();
	mInitPosision = this->getPosition();
}


