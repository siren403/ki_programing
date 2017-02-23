#include "TileBlackBlock.h"
#include "StopWatch.h"
#include "ColorUtil.h"

#define GLPROGRAM_NAME "gl_black_floor"
#define PI 3.1415

bool TileBlackBlock::init()
{
	if (!MapTile::init())
	{
		return false;
	}

	mTileSprite = Sprite::create("tile/tile_black_wall.png");
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
	mGLState->setUniformVec3("pointColor", Vec3(1, 0, 1));
	mGLState->setUniformVec3("changeColor", ColorUtil::Convert255ToOne(90, 220, 90));
	mGLState->setUniformFloat("colorRatio", .0f);
	mTileSprite->setGLProgramState(mGLState);

	mDuration = 0.35;

	this->scheduleUpdate();

	return true;
}

void TileBlackBlock::update(float dt)
{
	if (mIsHighlight)
	{
		if (mStopWatch->GetAccTime() >= mDuration)
		{
			mIsHighlight = false;
			mStopWatch->OnStop();
		}
		mGLState->setUniformFloat("colorRatio", sin(PI * (mStopWatch->GetAccTime() / mDuration)));
	}
}

void TileBlackBlock::SetHighlight(bool isHighlight)
{
	if (isHighlight)
	{
		mIsHighlight = true;
		mStopWatch->OnStart();
	}
}
