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

	mNextStates.push_back(Juggler::State::State_SeqAttack);
	mNextStates.push_back(Juggler::State::State_RushAttack);
	mNextStates.push_back(Juggler::State::State_CornerAttack);
	mNextStates.push_back(Juggler::State::State_ColRowAttack);

	
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
		pos = ccpLerp(this->GetEntity()->getPosition(), player->getPosition(), dt * 0.25);
		this->GetEntity()->setPosition(pos);

		mStopWatch->OnUpdate(dt);

		if (mStopWatch->GetAccTime() > 2.5)
		{
			//NextState

			mEntity->ChangeState(mNextStates[random(0, (int)mNextStates.size() - 1)]);
			//mEntity->ChangeState(Juggler::State::State_SeqAttack);
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
			this->GetEntity<Juggler>()->ChangeState(random(0.0f, 1.0f) > 0.5f ? Juggler::State::State_Idle : Juggler::State::State_ColRowAttack);
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
	EasingType type = random(0.0f, 1.0f) > 0.5f ? EasingType::Ease_ExpoOut: EasingType::Ease_ExpoIn;

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
			mEntity->ChangeState(random(0.0f, 1.0f) > 0.5 ? Juggler::State::State_Idle : Juggler::State::State_CornerAttack);
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
	mCornerPostions[1] = Vec2(mMapSize.width * 0.8, mMapSize.height * 0.8);
	mCornerPostions[2] = Vec2(mMapSize.width * 0.2, mMapSize.height * 0.2);
	mCornerPostions[3] = Vec2(mMapSize.width * 0.8, mMapSize.height * 0.2);
	mCornerIndex = 0;

#pragma region corner patters

	mCornerPositionPatterns[0][0] = 0;
	mCornerPositionPatterns[0][1] = 1;
	mCornerPositionPatterns[0][2] = 2;
	mCornerPositionPatterns[0][3] = 3;

	mCornerPositionPatterns[1][0] = 2;
	mCornerPositionPatterns[1][1] = 1;
	mCornerPositionPatterns[1][2] = 3;
	mCornerPositionPatterns[1][3] = 0;

	mCornerPositionPatterns[2][0] = 3;
	mCornerPositionPatterns[2][1] = 0;
	mCornerPositionPatterns[2][2] = 1;
	mCornerPositionPatterns[2][3] = 2;

	mCornerPositionPatterns[3][0] = 1;
	mCornerPositionPatterns[3][1] = 2;
	mCornerPositionPatterns[3][2] = 0;
	mCornerPositionPatterns[3][3] = 3;

#pragma endregion


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
	mCornerPatternIndex = random(0, 3);
	mStartPosition = mEntity->getPosition();
	//mMoveEasingData

	InitMoveEasingData(EasingType::Ease_QuadInOut, mStartPosition, GetCornerPosition(mCornerIndex));
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
		InitMoveEasingData(EasingType::Ease_QuadInOut, GetCornerPosition(start), GetCornerPosition(end));
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
	mMoveXEasingData.duration = 1.6;

	mMoveYEasingData.type = type;
	mMoveYEasingData.currentTime = 0;
	mMoveYEasingData.startValue = start.y;
	mMoveYEasingData.changeValue = end.y - start.y;
	mMoveYEasingData.duration = 1.6;
}
Vec2 JugglerCornerAttackState::GetCornerPosition(int index)
{
	return mCornerPostions[mCornerPositionPatterns[mCornerPatternIndex][index]];
}
#pragma endregion

#pragma region VerticalAttack

bool JugglerColRowAttack::InitState()
{
	if (!EnemyFiniteState::InitState())
	{
		return false;
	}

	mMapSize = ActorManager::GetInstance()->GetPlayMap()->GetMapContentSize();
	mCircleCount = GetEntity<Juggler>()->GetCircleCount() + 1;//parts + lifeParts
	mCircles.reserve(mCircleCount);
	mInitPositions.reserve(mCircleCount);
	mPrevPositions.reserve(mCircleCount);


	Vec2 tempPos;
	for (int i = 0; i < mCircleCount; i++)
	{
		mInitPositions.push_back(Vec2::ZERO);
		mPrevPositions.push_back(Vec2::ZERO);
	}


	mStopWatch = StopWatch::create();
	mStopWatch->retain();
	mStopWatch->OnStart();

	return true;
}

JugglerColRowAttack::~JugglerColRowAttack()
{
	CC_SAFE_RELEASE_NULL(mStopWatch);
}

void JugglerColRowAttack::OnEnter()
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
	mInitEntityPosition = this->mEntity->getPosition();
	//mState = State::State_VerticalPosition;
	mState = random(0.0f, 1.0f) > 0.5 ? State::State_HorizonPosition : State::State_VerticalPosition;

}

void JugglerColRowAttack::OnUpdate(float dt)
{
	mStopWatch->OnUpdate(dt);
	switch (mState)
	{
	case JugglerColRowAttack::State_VerticalPosition:
		UpdateVerticalPosition(dt);
		break;
	case JugglerColRowAttack::State_VerticalMove:
		UpdateVerticalMove(dt);
		break;
	case JugglerColRowAttack::State_HorizonPosition:
		UpdateHorizonPosition(dt);
		break;
	case JugglerColRowAttack::State_HorizonMove:
		UpdateHorizonMove(dt);
		break;
	case JugglerColRowAttack::State_ReturnInitPosition:
		UpdateReturnInitPosition(dt);
		break;
	
	}
}

void JugglerColRowAttack::OnExit()
{
	mCircles.clear();
	mStopWatch->OnReset();
	JugglerCircle * circle = nullptr;

	for (int i = 0; i < GetEntity<Juggler>()->GetCircleCount(); i++)
	{
		circle = (JugglerCircle*)mEntity->GetPartsMap()->at(i);
		circle->SetState(JugglerCircle::State::State_Idle);
	}
}
void JugglerColRowAttack::UpdateVerticalPosition(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1;

	Vec2 pos;

	for (int i = 0; i < mCircleCount; i++)
	{

		data.startValue = mInitPositions[i].x;
		data.changeValue = mEntity->getPosition().x - data.startValue;
		pos.x = EasingFunc::Ease(data);

		data.startValue = mInitPositions[i].y;
		data.changeValue = (mMapSize.height * (i * 0.07)) + mMapSize.height * 0.1 - data.startValue;
		pos.y = EasingFunc::Ease(data);

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}

	data.startValue = mEntity->getPosition().x;
	data.changeValue = (mMapSize.width * 0.1) - data.startValue;
	pos.x = EasingFunc::Ease(data);
	pos.y = mEntity->getPosition().y;
	mEntity->setPosition(pos);

	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		mState = State::State_VerticalMove;
	}
}
void JugglerColRowAttack::UpdateVerticalMove(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.duration = 2.6f;
	data.currentTime = sin(PI * (mStopWatch->GetAccTime()/data.duration)) * data.duration;

	Vec2 pos;
	data.startValue = mMapSize.width * 0.1;
	data.changeValue = (mMapSize.width * 0.9) - data.startValue;
	pos.x = EasingFunc::Ease(data);
	pos.y = mEntity->getPosition().y;
	mEntity->setPosition(pos);

	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		SavePrevPosition();
		mState = State::State_ReturnInitPosition;
	}
}
void JugglerColRowAttack::UpdateHorizonPosition(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 1;

	Vec2 pos;

	for (int i = 0; i < mCircleCount; i++)
	{
		data.startValue = mInitPositions[i].x;
		data.changeValue = (mMapSize.width * (i * 0.06)) + mMapSize.width * 0.13 - data.startValue;
		pos.x = EasingFunc::Ease(data);

		data.startValue = mInitPositions[i].y;
		data.changeValue = (mMapSize.height * 0.9) - data.startValue;
		pos.y = EasingFunc::Ease(data);

		pos = mEntity->getParent()->convertToWorldSpace(pos);
		pos = mEntity->convertToNodeSpace(pos);
		mCircles.at(i)->setPosition(pos);
	}

	pos.x = mEntity->getPosition().x;

	data.startValue = mEntity->getPosition().y;
	data.changeValue = (mMapSize.height * 0.9) - data.startValue;
	pos.y = EasingFunc::Ease(data);
	mEntity->setPosition(pos);

	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		mState = State::State_HorizonMove;
	}
}
void JugglerColRowAttack::UpdateHorizonMove(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.duration = 2.6f;
	data.currentTime = sin(PI * (mStopWatch->GetAccTime() / data.duration)) * data.duration;

	Vec2 pos;
	data.startValue = mMapSize.height * 0.9;
	data.changeValue = (mMapSize.height * 0.1) - data.startValue;
	pos.x = mEntity->getPosition().x;
	pos.y = EasingFunc::Ease(data);
	mEntity->setPosition(pos);

	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		SavePrevPosition();
		mState = State::State_ReturnInitPosition;
	}
}
void JugglerColRowAttack::UpdateReturnInitPosition(float dt)
{
	EasingData data;
	data.type = EasingType::Ease_QuadInOut;
	data.currentTime = mStopWatch->GetAccTime();
	data.duration = 0.8;

	Vec2 pos;
	for (int i = 0; i < mCircleCount; i++)
	{
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

	data.startValue = mPrevEntityPosition.x;
	data.changeValue = mInitEntityPosition.x - data.startValue;
	pos.x = EasingFunc::Ease(data);

	data.startValue = mPrevEntityPosition.y;
	data.changeValue = mInitEntityPosition.y - data.startValue;
	pos.y = EasingFunc::Ease(data);

	mEntity->setPosition(pos);

	if (mStopWatch->GetAccTime() >= data.duration)
	{
		mStopWatch->OnReset();
		mEntity->ChangeState(Juggler::State::State_CornerAttack);
	}
}



void JugglerColRowAttack::SavePrevPosition()
{
	for (int i = 0; i < mCircleCount; i++)
	{
		mPrevPositions[i] = mEntity->convertToWorldSpace(mCircles.at(i)->getPosition());
		mPrevPositions[i] = mEntity->getParent()->convertToNodeSpace(mPrevPositions[i]);
	}
	mPrevEntityPosition = this->mEntity->getPosition();
}
#pragma endregion
