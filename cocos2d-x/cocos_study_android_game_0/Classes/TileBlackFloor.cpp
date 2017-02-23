#include "TileBlackFloor.h"
#include "StopWatch.h"

#define GLPROGRAM_NAME "gl_black_floor"
#define PI 3.1415

bool TileBlackFloor::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_black_floor.png");
	mTileSprite->getTexture()->setAliasTexParameters();
	this->addChild(mTileSprite, 0);

	mDurationWatch = StopWatch::create();
	mDurationWatch->SetAutoUpdate(true);
	this->addChild(mDurationWatch);

	mDelayWatch = StopWatch::create();
	mDelayWatch->SetAutoUpdate(true);
	this->addChild(mDelayWatch);

	auto glCache = GLProgramCache::getInstance();

	if (glCache->getGLProgram(GLPROGRAM_NAME) == nullptr)
	{
		auto glProg = GLProgram::createWithFilenames(
			"shader/ccPositionTextureColor_noMVP_vert.vsh", "shader/pointColor.fsh");
		glCache->addGLProgram(glProg, GLPROGRAM_NAME);
		log("create glProgram");
	}


	mGLState = GLProgramState::create(glCache->getGLProgram(GLPROGRAM_NAME));
	mGLState->setUniformVec3("pointColor", Vec3(1, 0, 1));
	mGLState->setUniformVec3("changeColor", Vec3(0.4, 0.1, 0.1));
	mGLState->setUniformFloat("colorRatio", .0f);
	mTileSprite->setGLProgramState(mGLState);

	mDuration = 0.6;

	this->scheduleUpdate();
	return true;
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
			mGLState->setUniformFloat("colorRatio", sin(PI * (mDurationWatch->GetAccTime() / mDuration)));
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
