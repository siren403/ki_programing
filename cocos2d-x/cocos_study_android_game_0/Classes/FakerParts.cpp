#include "FakerParts.h"
#include "StopWatch.h"

bool FakerSheep::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("enemy/sheep.png"));

	mFaceSprite = Sprite::create(
		StringUtils::format("enemy/sheep_face_%d.png", mFaceIndex));
	mFaceSprite->setPosition(Vec2(38, 55));
	mFaceSprite->getTexture()->setAliasTexParameters();
	sprite->addChild(mFaceSprite);


	mStopWatch = StopWatch::create();
	mStopWatch->OnStart();
	this->addChild(mStopWatch);

	this->scheduleUpdate();
	return true;
}

void FakerSheep::update(float dt)
{
	mStopWatch->OnUpdate(dt);

	if (mStopWatch->GetAccTime() > 1)
	{
		mStopWatch->OnReset();
		mFaceIndex++;
		mFaceSprite->setTexture(StringUtils::format("enemy/sheep_face_%d.png", mFaceIndex));
		mFaceSprite->getTexture()->setAliasTexParameters();
		if (mFaceIndex == 4)
		{
			mFaceIndex = 0;
		}
	}

}
