#include "CSimpleAnimate.h"




Action * CSimpleAnimate::CreateAction(const char *tFrameNamePattern, int tStart, int tEnd)
{
	int ti = 0;
	Vector<SpriteFrame *> tSpriteFrameVec;
	SpriteFrame * tSpriteFrame = NULL;
	std::string tStr;

	for (ti = tStart; ti <= tEnd; ti++)
	{
		tSpriteFrame = NULL;
		tStr = StringUtils::format(tFrameNamePattern, ti);
		/*log(tFrameNamePattern, ti);*/

		tSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tStr);
		tSpriteFrameVec.pushBack(tSpriteFrame);
	}

	auto tAnimation = Animation::createWithSpriteFrames(tSpriteFrameVec, 0.3f);
	auto tAnimate = Animate::create(tAnimation);

	auto tAnimateAction = RepeatForever::create(tAnimate);
	
	return tAnimateAction;
}


void CSimpleAnimate::addPlist(const std::string & tFileName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(tFileName);
}

void CSimpleAnimate::removePlist(const std::string & tFileName)
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(tFileName);
}


