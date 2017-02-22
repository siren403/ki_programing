#include "JugglerFiniteState.h"
#include "Juggler.h"
#include "JugglerParts.h"
#include "StopWatch.h"
#include "ActorManager.h"
#include "Player.h"

#define PI 3.14159

#pragma region None

bool JugglerNoneState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	return true;
}

JugglerNoneState::~JugglerNoneState()
{
}

void JugglerNoneState::OnEnter()
{
	

}

void JugglerNoneState::OnUpdate(float dt)
{
}

void JugglerNoneState::OnExit()
{
}

#pragma endregion

#pragma region Idle

bool JugglerIdleState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}
	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();
	
	return true;
}

JugglerIdleState::~JugglerIdleState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerIdleState::OnEnter()
{
	auto circles = this->GetEntity<Juggler>();
	Vec2 pos;
	for (int i = 0; i < circles->GetCircleCount(); i++)
	{
		((JugglerCircle*)circles->GetPartsMap()->at(i))->SetState(JugglerCircle::State::State_Idle);
	}
}

void JugglerIdleState::OnUpdate(float dt)
{
	if (mIsActive)
	{
		auto player = ActorManager::GetInstance()->GetPlayer();
		Vec2 pos;
		pos = ccpLerp(this->GetEntity()->getPosition(), player->getPosition(), dt * 0.1);
		this->GetEntity()->setPosition(pos);

		mStopWatch->OnUpdate(dt);

		if (mStopWatch->GetAccTime() > 4)
		{
			//NextState

			float r = random(0, 1);
			if (r < 0.5)
			{
				this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_SeqAttack);
			}
			else
			{
				this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_RushAttack);
			}
			mStopWatch->OnReset();
		}
	}
}

void JugglerIdleState::OnExit()
{

}

#pragma endregion

#pragma region SeqAttack

bool JugglerSeqAttackState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();


	return true;
}

JugglerSeqAttackState::~JugglerSeqAttackState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerSeqAttackState::OnEnter()
{
	for (int i = 0; i < this->GetEntity<Juggler>()->GetCircleCount(); i++)
	{
		auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(i);
		circle->SetState(JugglerCircle::State::State_None);
	}
}

void JugglerSeqAttackState::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	int circleCount = this->GetEntity<Juggler>()->GetCircleCount();
	float attackDuration = 3;
	if (mCurrentAttackIndex <  circleCount)
	{
		if (mStopWatch->GetAccTime() >= 0.8)
		{
			auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(mCurrentAttackIndex);
			Vec2 targetPos = ActorManager::GetInstance()->ConvertPlayerToEntity(mEntity);
			circle->OnAttack(targetPos, attackDuration);
			mCurrentAttackIndex++;
			
			mStopWatch->OnReset();
		}
	}
	else
	{
		auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(mCurrentAttackIndex - 1);
		if (circle->GetState() == JugglerCircle::State::State_None)
		{
			mCurrentAttackIndex = 0;
			this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_Idle);
			mStopWatch->OnReset();
		}
	}
}

void JugglerSeqAttackState::OnExit()
{
}
#pragma endregion

#pragma region RushAttack

bool JugglerRushAttackState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	mChargeDuration = 3;
	mChargeRotationRatio = 6;
	mChargeRadius = 0.5;

	mRushDuration = 3;
	mRushRadius = 4;

#pragma region Easing Data
	
	mEaseChargeRotateData.startValue = 1;
	mEaseChargeRotateData.changeValue = mChargeRotationRatio - 1;
	mEaseChargeRotateData.duration = mChargeDuration;

	mEaseOutRadiusData.startValue = mChargeRadius;
	mEaseOutRadiusData.changeValue = mRushRadius - mChargeRadius;
	mEaseOutRadiusData.duration = mRushDuration / 2;

#pragma endregion
	return true;
}

JugglerRushAttackState::~JugglerRushAttackState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerRushAttackState::OnEnter()
{
	float r = random(0.0f, 1.0f);
	EasingType type;
	if (r < 0.3f)
	{
		type = EasingType::Ease_ExpoOut;
	}
	else if (r < 0.6f)
	{
		type = EasingType::Ease_ExpoIn;
	}
	else
	{
		type = EasingType::Ease_Linear;
	}
	mEaseChargeRotateData.type = type;
	mEaseOutRadiusData.type = type;


	for (int i = 0; i < this->GetEntity<Juggler>()->GetCircleCount(); i++)
	{
		auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(i);
		circle->SetState(JugglerCircle::State::State_Idle);
	}
}

void JugglerRushAttackState::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	if (mIsCharging == false)//charge
	{
		for (int i = 0; i < this->GetEntity<Juggler>()->GetCircleCount(); i++)
		{
			auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(i);

			mEaseChargeRotateData.currentTime = mStopWatch->GetAccTime();

			float ratio = EasingFunc::Ease(mEaseChargeRotateData);
			circle->SetRotateSpeedRatio(ratio);

			ratio = EasingFunc::EaseLinear(
				mStopWatch->GetAccTime(), 1, mChargeRadius - 1, mChargeDuration);
			circle->SetCircleRadiusRatio(ratio);
		}
		if (mStopWatch->GetAccTime() >= mChargeDuration)
		{
			mIsCharging = true;
			mStopWatch->OnReset();

			
		}
	}
	else//rush
	{
		for (int i = 0; i < this->GetEntity<Juggler>()->GetCircleCount(); i++)
		{
			auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(i);
			float ratio;

			if (mIsRushReturn == false)
			{
				//radius out
				mEaseOutRadiusData.currentTime = mStopWatch->GetAccTime();

				ratio = EasingFunc::Ease(mEaseOutRadiusData);
				circle->SetCircleRadiusRatio(ratio);
				if (mStopWatch->GetAccTime() >= mRushDuration / 2)
				{
					mIsRushReturn = true;
					mStopWatch->OnReset();
				}
			}
			else
			{
				//radius in, rotate in
				ratio = EasingFunc::EaseLinear(
					mStopWatch->GetAccTime(), mChargeRotationRatio, 1 - mChargeRotationRatio, mRushDuration / 2);
				circle->SetRotateSpeedRatio(ratio);

				ratio = EasingFunc::EaseLinear(
					mStopWatch->GetAccTime(), mRushRadius, 1 - mRushRadius, mRushDuration / 2);
				circle->SetCircleRadiusRatio(ratio);
			}
		}
		if (mStopWatch->GetAccTime() >= mRushDuration / 2)
		{
			mIsRushReturn = false;
			mIsCharging = false;
			mStopWatch->OnReset();
			mEntity->ChangeState(Juggler::State::State_Idle);
		}
	}
}

void JugglerRushAttackState::OnExit()
{
}

#pragma endregion

