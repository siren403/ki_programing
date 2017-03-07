#include "TileBlackFloor.h"
#include "StopWatch.h"
#include "ColorUtil.h"
#include "SWPointColor.h"

#define GLPROGRAM_NAME "gl_black_floor"
#define PI 3.1415


bool TileBlackFloor::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_black_floor_1.png");
	mTileSprite->getTexture()->setAliasTexParameters();
	this->addChild(mTileSprite, 0);

	mDurationWatch = StopWatch::create();
	mDurationWatch->SetAutoUpdate(true);
	this->addChild(mDurationWatch);

	mDelayWatch = StopWatch::create();
	mDelayWatch->SetAutoUpdate(true);
	this->addChild(mDelayWatch);


	mPointColor = new SWPointColor(mTileSprite);
	mPointColor->SetPointColor(Vec3(1, 0, 1));
	mPointColor->SetBaseColor(ColorUtil::Convert255ToOne(166, 154, 129));
	mPointColor->SetChangeColor(Vec3(0.85, 0.1, 0.1));
	mPointColor->SetColorRatio(.0f);

	mDuration = 1.8;

	this->scheduleUpdate();
	return true;
}
TileBlackFloor::~TileBlackFloor()
{
	CC_SAFE_DELETE(mPointColor);
}

void TileBlackFloor::update(float dt)
{
	if (mIsHighlight)
	{
		if (mDelay == 0)
		{
			if (mDurationWatch->GetAccTime() >= mDuration)
			{
				mIsHighlight = false;
				mDurationWatch->OnStop();
			}
			mPointColor->SetColorRatio(sin(PI * (mDurationWatch->GetAccTime() / mDuration)));
		}
		else
		{
			if (mDelayWatch->GetAccTime() >= mDelay)
			{
				mDelay = 0;
				mDelayWatch->OnStop();
				mDurationWatch->OnStart();
			}
		}
	}
}

void TileBlackFloor::SetHighlight(bool isHighlight)
{
	if (isHighlight)
	{
		mIsHighlight = true;
		mDurationWatch->OnStart();
	}
}

void TileBlackFloor::SetHighlight(bool isHighlight, float delay)
{
	if (mIsHighlight)
	{
		return;
	}

	if (isHighlight)
	{
		mIsHighlight = true;
		mDelayWatch->OnStart();
		mDelay = delay;
	}
}
