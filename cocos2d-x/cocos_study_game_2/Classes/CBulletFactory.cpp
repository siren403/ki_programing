#include "CBulletFactory.h"

#include "CBulletPattern.h"
#include "CBulletDirection.h"
#include "CBulletCurve.h"

CBullet * CBulletFactory::creataBullet3Way(DirSpeed tLeft, DirSpeed tCenter, DirSpeed tRight)
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

CBullet * CBulletFactory::creataBulletCurveSide3Way(DirSpeed tTop, DirSpeed tCenter, DirSpeed tBot, float radius)
{

	CBulletPattern * tTempPattern = nullptr;
	CBulletDirection * tDir = nullptr;
	CBulletCurve * tCurve = nullptr;

	tTempPattern = CBulletPattern::create();
	tTempPattern->bulletReserve(3);

	tCurve = CBulletCurve::create();
	tCurve->setDirection(tTop.mDir);
	tCurve->setSpeed(tTop.mSpeed);
	tCurve->setRadius(radius);
	tTempPattern->pushBullet(tCurve);

	tDir = CBulletDirection::create();
	tDir->setDirection(tCenter.mDir);
	tDir->setSpeed(tCenter.mSpeed);
	tTempPattern->pushBullet(tDir);

	tCurve = CBulletCurve::create();
	tCurve->setDirection(tBot.mDir);
	tCurve->setSpeed(tBot.mSpeed);
	tCurve->setRadius(radius);
	tTempPattern->pushBullet(tCurve);

	return tTempPattern;
}
