#include "BulletFactory.h"

#include "CBulletPattern.h"
#include "CBulletDirection.h"

CBullet * BulletFactory::creataBullet3Way(DirSpeed tLeft, DirSpeed tCenter, DirSpeed tRight)
{
	CBulletPattern * tTempPattern = nullptr;
	CBulletDirection * tTempBullet = nullptr;

	tTempPattern = CBulletPattern::create();
	tTempPattern->bulletReserve(3);

	tTempBullet = CBulletDirection::create();
	tTempBullet->setDirection(tLeft.mDir);
	tTempBullet->setSpeed(tLeft.mSpeed);
	tTempPattern->pushBullet(tTempBullet);

	tTempBullet = CBulletDirection::create();
	tTempBullet->setDirection(tCenter.mDir);
	tTempBullet->setSpeed(tCenter.mSpeed);
	tTempPattern->pushBullet(tTempBullet);

	tTempBullet = CBulletDirection::create();
	tTempBullet->setDirection(tRight.mDir);
	tTempBullet->setSpeed(tRight.mSpeed);
	tTempPattern->pushBullet(tTempBullet);

	return tTempPattern;
}
