#include "JugglerFiniteState.h"
#include "Juggler.h"
#include "JugglerParts.h"
#include "StopWatch.h"
#include "ActorManager.h"
#include "Player.h"
#include "IntUtils.h"
#include "PlayMap.h"
#include "MapTile.h"

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

			/*float r = random(0, 1);
			if (r < 0.3)
				this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_SeqAttack);
			else
				this->GetEntity<Juggler>()->ChangeState(Juggler::State::State_RushAttack);		
			*/

			//this->mEntity->ChangeState(Juggler::State::State_CornerAttack);
			this->mEntity->ChangeState(Juggler::State::State_VerticalAttack);
			mStopWatch->OnReset();
		}
	}
}

void JugglerIdleState::OnExit()
{
	mStopWatch->OnReset();
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
	mCurrentAttackIndex = 0;
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
	if (mCurrentAttackIndex <  circleCount)
	{
		if (mStopWatch->GetAccTime() >= 0.8)
		{
			auto circle = (JugglerCircle*)this->GetEntity<Juggler>()->GetParts(mCurrentAttackIndex);
			Vec2 targetPos = ActorManager::GetInstance()->ConvertPlayerToEntity(mEntity);
			circle->OnAttack(targetPos, 2.7);

			auto tile = ActorManager::GetInstance()->GetPlayMap()->GetTile(
				ActorManager::GetInstance()->GetPlayer()->getPosition());
			tile->SetHighlight(true);

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
	mStopWatch->OnReset();
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
	mChargeRadiusRatio = 0.5;

	mRushDuration = 3;
	mRushRadiusRatio = 4;

#pragma region Easing Data
	
	mEaseChargeRotateData.startValue = 1;
	mEaseChargeRotateData.changeValue = mChargeRotationRatio - 1;
	mEaseChargeRotateData.duration = mChargeDuration;

	mEaseOutRadiusData.startValue = mChargeRadiusRatio;
	mEaseOutRadiusData.changeValue = mRushRadiusRatio - mChargeRadiusRatio;
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
#pragma region Rush Init
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
#pragma endregion
#pragma region warning

	auto map = ActorManager::GetInstance()->GetPlayMap();
	Vec2I posIndex = map->GetTileIndex(mEntity->getPosition());
	MapTile * tempTile = nullptr;
	Vec2I curTileIndex;
	Vec2I distance;
	float radius;
	float rushRange = GetEntity<Juggler>()->GetCircleRadius() * mRushRadiusRatio / map->GetTileWidth();
	for (int y = 0; y < map->GetMapHeight(); y++)
	{
		for (int x = 0; x < map->GetMapWidth(); x++)
		{
			curTileIndex = Vec2I(x, y);
			distance = curTileIndex - posIndex;
			radius = sqrt(IntUtils::Dot(distance, distance));

			if (radius < rushRange)
			{
				map->GetTile(curTileIndex)->SetHighlight(true, mChargeDuration * 0.7 + radius * 0.05);
			}
		}
	}

	map->GetTile(mEntity->getPosition())->SetHighlight(true, 0);

#pragma endregion

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
				mStopWatch->GetAccTime(), 1, mChargeRadiusRatio - 1, mChargeDuration);
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
					mStopWatch->GetAccTime(), mRushRadiusRatio, 1 - mRushRadiusRatio, mRushDuration / 2);
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
	mStopWatch->OnReset();
	mIsCharging = false;
	mIsRushReturn = false;
}

#pragma endregion

#pragma region CornerAttack

bool JugglerCornerAttackState::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	Size mMapSize = ActorManager::GetInstance()->GetPlayMap()->GetMapContentSize();

	mCornerPostions[0] = Vec2(mMapSize.width * 0.2, mMapSize.height * 0.8);
	mCornerPostions[3] = Vec2(mMapSize.width * 0.8, mMapSize.height * 0.8);
	mCornerPostions[2] = Vec2(mMapSize.width * 0.2, mMapSize.height * 0.2);
	mCornerPostions[1] = Vec2(mMapSize.width * 0.8, mMapSize.height * 0.2);
	mCornerIndex = 0;

	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	return true;
}

JugglerCornerAttackState::~JugglerCornerAttackState()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerCornerAttackState::OnEnter()
{
	mCornerIndex = 0;
	mStartPosition = mEntity->getPosition();
	//mMoveEasingData

	InitMoveEasingData(EasingType::Ease_QuadInOut, mStartPosition, mCornerPostions[mCornerIndex]);
}

void JugglerCornerAttackState::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	if (mStopWatch->GetAccTime() < mMoveXEasingData.duration)
	{
		Vec2 pos;
		mMoveXEasingData.currentTime = mStopWatch->GetAccTime();
		pos.x = EasingFunc::Ease(mMoveXEasingData);
		mMoveYEasingData.currentTime = mStopWatch->GetAccTime();
		pos.y = EasingFunc::Ease(mMoveYEasingData);

		mEntity->setPosition(pos);
	}
	else
	{
		mStopWatch->OnReset();
		if (mCornerIndex == 4)
		{
			mEntity->ChangeState(Juggler::State::State_Idle);
			return;
		}

		int start = mCornerIndex;
		int end = ++mCornerIndex;
		if (end == 4)
		{
			end = 0;
		}
		InitMoveEasingData(EasingType::Ease_QuadInOut, mCornerPostions[start], mCornerPostions[end]);
	}
}

void JugglerCornerAttackState::OnExit()
{
	mCornerIndex = 0;
	mStopWatch->OnReset();
}
void JugglerCornerAttackState::InitMoveEasingData(EasingType type, Vec2 start, Vec2 end)
{
	mMoveXEasingData.type = type;
	mMoveXEasingData.currentTime = 0;
	mMoveXEasingData.startValue = start.x;
	mMoveXEasingData.changeValue = end.x - start.x;
	mMoveXEasingData.duration = 2;

	mMoveYEasingData.type = type;
	mMoveYEasingData.currentTime = 0;
	mMoveYEasingData.startValue = start.y;
	mMoveYEasingData.changeValue = end.y - start.y;
	mMoveYEasingData.duration = 2;
}
#pragma endregion

#pragma region VerticalAttack

bool JugglerVerticalAttack::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mMapSize = ActorManager::GetInstance()->GetPlayMap()->GetMapContentSize();
	mCircleCount = GetEntity<Juggler>()->GetCircleCount() + 1;//parts + lifeParts
	mCircles.reserve(mCircleCount);
	mInitPositions.reserve(mCircleCount);
	mLeftPositions.reserve(mCircleCount);
	mPrevPositions.reserve(mCircleCount);


	Vec2 tempPos;
	for (int i = 0; i < mCircleCount; i++)
	{
		mInitPositions.push_back(Vec2::ZERO);
		tempPos.x = mMapSize.width * 0.1;
		tempPos.y = (mMapSize.height * (i * 0.07)) + mMapSize.height * 0.1;
		mLeftPositions.push_back(tempPos);

		mPrevPositions.push_back(Vec2::ZERO);
	}


	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	return true;
}

JugglerVerticalAttack::~JugglerVerticalAttack()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerVerticalAttack::OnEnter()
{
	JugglerCircle * circle = nullptr;

	int lifeCircleIndex = random(0, mCircleCount - 2);
	for (int i = 0; i < mCircleCount - 1; i++)
	{
		circle = (JugglerCircle*)mEntity->GetPartsMap()->at(i);
		
		circle->SetState(JugglerCircle::State::State_None);
		mCircles.pushBack(circle);
		if (i == lifeCircleIndex)
		{
			circle = (JugglerCircle*)mEntity->GetParts(LIFEPARTS_KEY);
			mCircles.pushBack(circle);
		}
	}
	for (int i = 0; i < mCircleCount; i++)
	{
		circle = mCircles.at(i);
		mInitPositions[i] = mEntity->convertToWorldSpace(circle->getPosition());
		mInitPositions[i] = mEntity->getParent()->convertToNodeSpace(mInitPositions[i]);
	}
	mState = State::State_MoveStartPosition;
}

void JugglerVerticalAttack::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	switch (mState)
	{
	case JugglerVerticalAttack::State_MoveStartPosition:
		UpdateMoveStartPosition(dt);
		break;
	case JugglerVerticalAttack::State_LeftToRight:
		UpdateLeftToRight(dt);
		break;
	case JugglerVerticalAttack::State_RightToLeft:
		UpdateRightToLeft(dt);
		break;
	case JugglerVerticalAttack::State_ReturnInitPosition:
		UpdateReturnInitPosition(dt);
		break;
	}
}

void JugglerVerticalAttack::OnExit()
{
	mCircles.clear();
	mStopWatch->OnReset();
}
void JugglerVerticalAttack::UpdateMoveStartPosition(float dt)
{

	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1;

	for (int i = 0; i < mCircleCount; i++)
	{
		Vec2 pos;

		data.startValue = mInitPositions[i].x;
		data.changeValue = mLeftPositions[i].x - data.startValue;
		pos.x = EasingFunc::Ease(data);

		data.startValue = mInitPositions[i].y;
		data.changeValue = mLeftPositions[i].y - data.startValue;
		pos.y = EasingFunc::Ease(data);

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}
	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		SavePrevPosition();
		mState = State::State_LeftToRight;
	}
}
void JugglerVerticalAttack::UpdateLeftToRight(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1.3f;

	for (int i = 0; i < mCircleCount; i++)
	{
		Vec2 pos;

		data.startValue = mLeftPositions[i].x;
		data.changeValue = (mMapSize.width * 0.9) - data.startValue;
		pos.x = EasingFunc::Ease(data);

		pos.y = mLeftPositions[i].y;

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}
	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		SavePrevPosition();
		mState = State::State_RightToLeft;
	}
}
void JugglerVerticalAttack::UpdateRightToLeft(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1.3f;

	for (int i = 0; i < mCircleCount; i++)
	{
		Vec2 pos;

		data.startValue = mPrevPositions[i].x;
		data.changeValue = mLeftPositions[i].x - data.startValue;
		pos.x = EasingFunc::Ease(data);

		pos.y = mLeftPositions[i].y;

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}
	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		SavePrevPosition();
		mState = State::State_ReturnInitPosition;
	}
}
void JugglerVerticalAttack::UpdateReturnInitPosition(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1.3;

	for (int i = 0; i < mCircleCount; i++)
	{
		Vec2 pos;

		data.startValue = mPrevPositions[i].x;
		data.changeValue = mInitPositions[i].x - data.startValue;
		pos.x = EasingFunc::Ease(data);

		data.startValue = mPrevPositions[i].y;
		data.changeValue = mInitPositions[i].y - data.startValue;
		pos.y = EasingFunc::Ease(data);

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}
	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		mEntity->ChangeState(Juggler::State::State_Idle);
	}
}
void JugglerVerticalAttack::SavePrevPosition()
{
	for (int i = 0; i < mCircleCount; i++)
	{
		mPrevPositions[i] = mEntity->convertToWorldSpace(mCircles.at(i)->getPosition());
		mPrevPositions[i] = mEntity->getParent()->convertToNodeSpace(mPrevPositions[i]);
	}
}
#pragma endregion
