#include "CBulletPattern.h"

void CBulletPattern::pushBullet(CBullet * tBullet)
{
	mBullets.pushBack(tBullet);
	this->addChild(tBullet);
}
