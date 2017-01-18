#include "CTime.h"

void CTime::setTimeScale(float tTimeScale)
{
	Director::getInstance()->getScheduler()->setTimeScale(tTimeScale);
}

float CTime::getTimeScale()
{
	return Director::getInstance()->getScheduler()->getTimeScale();
}

