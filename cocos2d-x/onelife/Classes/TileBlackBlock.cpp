#include "TileBlackBlock.h"
#include "StopWatch.h"
#include "ColorUtil.h"
#include "SWPointColor.h"

#define PI 3.1415

bool TileBlackBlock::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_block_0.png");
	mTileSprite->getTexture()->setAliasTexParameters();
	this->addChild(mTileSprite, 0);

	mStopWatch = StopWatch::create();
	mStopWatch->SetAutoUpdate(true);
	this->addChild(mStopWatch);
	
	mDelayWatch = StopWatch::create();
	mDelayWatch->SetAutoUpdate(true);
	this->addChild(mDelayWatch);
	
	mShaderPointColor = new SWPointColor(mTileSprite);
	mShaderPointColor->SetPointColor(Vec3(1, 0, 1));
	mShaderPointColor->SetBaseColor(ColorUtil::Convert255ToOne(166, 154, 129));
	mShaderPointColor->SetChangeColor(ColorUtil::Convert255ToOne(255, 255, 255));
	mShaderPointColor->SetColorRatio(.0f);


	mDuration = 3.5f;

	this->scheduleUpdate();

	return true;
}

void TileBlackBlock::update(float dt)
{
	if (mDelayWatch->GetAccTime() >= mDelay)
	{
		mIsHighlight = true;
		mStopWatch->OnStart();
		mDelayWatch->OnStop();
	}

	if (mIsHighlight)
	{
		if (mStopWatch->GetAccTime() >= mDuration)
		{
			mStopWatch->OnReset();
		}
		mShaderPointColor->SetColorRatio(sin(PI * (mStopWatch->GetAccTime() / mDuration)));
	}
}

TileBlackBlock::~TileBlackBlock()
{
	CC_SAFE_DELETE(mShaderPointColor);
}

void TileBlackBlock::SetHighlight(bool isHighlight, float delay)
{
	if (mIsHighlight)
	{
		return;
	}
	if (isHighlight)
	{
		mDelayWatch->OnStart();
		mDelay = delay;
	}
}
