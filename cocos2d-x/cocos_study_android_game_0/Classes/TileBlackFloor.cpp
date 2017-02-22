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

	mStopWatch = StopWatch::create();
	mStopWatch->SetAutoUpdate(true);
	this->addChild(mStopWatch);


	auto glCache = GLProgramCache::getInstance();

	if (glCache->getGLProgram(GLPROGRAM_NAME) == nullptr)
	{
		auto glProg = GLProgram::createWithFilenames(
			"shader/ccPositionTextureColor_noMVP_vert.vsh", "shader/pointColor.fsh");
		glCache->addGLProgram(glProg, GLPROGRAM_NAME);
		log("create glProgram");
	}


	mGLState = GLProgramState::create(glCache->getGLProgram(GLPROGRAM_NAME));
	//if (mGLState->getReferenceCount() == 1)
	//{
	mGLState->setUniformVec3("pointColor", Vec3(1, 0, 1));
	mGLState->setUniformVec3("changeColor", Vec3(0.8, 0.2, 0.2));
	mGLState->setUniformFloat("colorRatio", .0f);
	//}
	mTileSprite->setGLProgramState(mGLState);

	this->scheduleUpdate();
	return true;
}

void TileBlackFloor::update(float dt)
{
	if (mIsHighlight)
	{
		if (mStopWatch->GetAccTime() >= PI)
		{
			if (mIsEndHighlight)
			{
				mIsEndHighlight = false;
				mIsHighlight = false;
				mStopWatch->OnStop();
			}
			else
			{
				mStopWatch->OnReset();
			}
		}
		mGLState->setUniformFloat("colorRatio", 0.5 * sin(mStopWatch->GetAccTime()));
	}
}

void TileBlackFloor::SetHighlight(bool isHighlight)
{
	if (isHighlight)
	{
		mIsHighlight = true;
		mStopWatch->OnStart();
	}
	else
	{
		mIsEndHighlight = true;
	}
}
