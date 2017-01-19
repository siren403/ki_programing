#include "CEnemyFactory.h"
#include "CEnemyParts.h"
#include "CBulletFactory.h"
#include "CBulletDirection.h"

CEnemy * CEnemyFactory::createBossSample(Layer * tBulletLayer)
{
	auto tBoss = CEnemy::create();

	CBullet * tBullet = nullptr;
	CEnemyParts * tParts = nullptr;


	tParts = CEnemyParts::create();
	tParts->setPosition(Vec2(0, 0));
	tParts->setHP(100);
	tParts->setBulletLayer(tBulletLayer);
	for (int i = 0; i < 3; i++)
	{
		tBullet = CBulletFactory::creataBullet3Way(
			DirSpeed(Vec2(-1, 0), 500),
			DirSpeed(Vec2(-1, -0.3), 500),
			DirSpeed(Vec2(-1, 0.3), 500)
		);
		tBullet->setColor(Color3B::RED);
		tParts->addBullet(tBullet);
	}
	tBoss->addParts(tParts);

	/*tParts = CEnemyParts::create();
	tParts->setPosition(Vec2(0, -100));
	tParts->setHP(100);
	tParts->setBulletLayer(tBulletLayer);
	for (int i = 0; i < 3; i++)
	{
		tBullet = CBulletFactory::creataBullet3Way(
			DirSpeed(Vec2(-1, 0), 500),
			DirSpeed(Vec2(-1, -0.3), 500),
			DirSpeed(Vec2(-1, 0.3), 500)
		);
		tBullet->setColor(Color3B::RED);
		tParts->addBullet(tBullet);
	}
	tBoss->addParts(tParts);*/

	/*tBullet = CBulletDirection::create();
	tBullet->setSpeed(400);
	tBullet->setDirection(Vec2(-1,0));
	tBullet->setColor(Color3B::RED);
	tParts->addBullet(tBullet);*/

	return tBoss;
}
