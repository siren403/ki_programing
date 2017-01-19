#ifndef __CENEMYFACTORY_H__
#define __CENEMYFACTORY_H__

#include "cocos2d.h"
#include "CEnemy.h"

using namespace cocos2d;

class CEnemyFactory
{
public:
	static CEnemy * createBossSample(Layer * tBulletLayer);
};

#endif // !__CENEMYFACTORY_H__
