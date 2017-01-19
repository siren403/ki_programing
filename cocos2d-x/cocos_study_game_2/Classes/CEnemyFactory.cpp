#include "CEnemyFactory.h"
#include "CEnemyParts.h"

CEnemy * CEnemyFactory::createBossSample(Layer * tBulletLayer)
{
	auto tBoss = CEnemy::create();

	auto tParts = CEnemyParts::create();
	tParts->setHP(100);

	

	tBoss->addParts(tParts);
	return tBoss;
}
