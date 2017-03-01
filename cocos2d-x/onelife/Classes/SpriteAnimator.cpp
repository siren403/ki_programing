#include "SpriteAnimator.h"


SpriteAnimator * SpriteAnimator::Create(
	const std::string& tAniFileName,
	int tStartFrame,
	int tEndFrame,
	float tDelayTime
)
{
	auto tInstance = SpriteAnimator::create();

	if (tInstance != nullptr)
	{
		tInstance->mAniFileName = tAniFileName;
		tInstance->mStartFrame = tStartFrame;
		tInstance->mEndFrame = tEndFrame;
		tInstance->mDelayTime = tDelayTime;
		tInstance->CreateAnimation();
	}

	return tInstance;
}

void SpriteAnimator::CreateAnimation()
{

	std::string tPlistName = mAniFileName + ".plist";
	std::string tFileName = mAniFileName + ".png";
	//log(tPlistName.c_str());
	//log(tFileName.c_str());

	auto tCache = SpriteFrameCache::getInstance();
	
	if (tCache->isSpriteFramesWithFileLoaded(tPlistName) == false)
	{
		tCache->addSpriteFramesWithFile(tPlistName, tFileName);
	}

	Vector<SpriteFrame *> tSpriteFrameVec;
	SpriteFrame * tSpriteFrame = nullptr;
	std::string tFrameName = "";

	char tStr[512];
	memset(tStr, 0, 512);
	

	for (int ti = mStartFrame; ti <= mEndFrame; ti++)
	{
		tSpriteFrame = nullptr;
		tFrameName = "";

		sprintf(tStr, "_%d.png", ti);
		tFrameName.append(mAniFileName);
		tFrameName.append(tStr);
		//log(tFrameName.c_str());


		tSpriteFrame = tCache->getSpriteFrameByName(tFrameName);

		tSpriteFrameVec.pushBack(tSpriteFrame);
	}

	auto tAnimation = Animation::createWithSpriteFrames(tSpriteFrameVec, mDelayTime);
	auto tAnimate = Animate::create(tAnimation);
	mpRepeat = RepeatForever::create(tAnimate);

	sprintf(tStr, "_%d.png", mStartFrame);
	mpSprite = Sprite::createWithSpriteFrameName(mAniFileName + tStr);
	this->addChild(mpSprite);

}

void SpriteAnimator::RunAni()
{
	mpSprite->runAction(mpRepeat);
}

void SpriteAnimator::StopAni()
{
	mpSprite->stopAction(mpRepeat);
}

Sprite * SpriteAnimator::GetSprite() const
{
	return mpSprite;
}

const Size & SpriteAnimator::GetContentSize() const
{
	return mpSprite->getContentSize();
}


