#include "CEnemyFactory.h"
#include "CEnemyParts.h"
#include "CBulletFactory.h"
#include "CBulletDirection.h"
#include "CBulletCurve.h";

#define DEFAULT_HP 100
#define BULLET_COUNT 30

CEnemy * CEnemyFactory::createBossSample(Layer * tBulletLayer)
{
	auto tCache = SpriteFrameCache::getInstance();
	if (tCache->isSpriteFramesWithFileLoaded("enemy_1.plist") == false)
	{
		tCache->addSpriteFramesWithFile("enemy_1.plist", "enemy_1.png");
	}


	auto tBoss = CEnemy::create();

	CBullet * tBullet = nullptr;
	CBulletDirection * tDir = nullptr;
	CBulletCurve * tCurve = nullptr;
	CEnemyParts * tParts = nullptr;
	Sprite * tSprite = nullptr;

#pragma region Body

	tParts = CEnemyParts::create();
	tSprite = Sprite::createWithSpriteFrameName("enemy_1_body_2.png");
	tParts->setSprite(tSprite);
	tParts->setPosition(Vec2(0, 0));
	tParts->setShotInterval(0.1);
	tParts->setShotOffset(Vec2(-50, 55));
	tParts->setHP(DEFAULT_HP * 2);
	tParts->setZOrder(5);
	tParts->setBulletLayer(tBulletLayer);
	for (int i = 0; i < 13; i++)
	{
		tCurve = CBulletCurve::create();
		tCurve->setDirection(Vec2(-1, -1));
		tCurve->setSpeed(500);
		tCurve->setRadius(500);
		tCurve->setColor(Color3B::RED);
		tParts->addBullet(tCurve);
	}
	tBoss->addParts(tParts);
#pragma endregion

#pragma region Head
	tParts = CEnemyParts::create();
	tSprite = Sprite::createWithSpriteFrameName("enemy_1_head.png");
	tSprite->setAnchorPoint(Vec2(0.5, 0));
	
	tParts->setSprite(tSprite);
	tParts->setPosition(Vec2(28, tSprite->getContentSize().height * 0.37));
	tParts->setShotInterval(0.3);
	tParts->setShotOffset(Vec2(-50, 155));
	tParts->setHP(DEFAULT_HP * 0.6);
	tParts->setZOrder(6);
	tParts->setBulletLayer(tBulletLayer);

	for (int i = 0; i < 4; i++)
	{
		tBullet = CBulletDirection::create();
		tBullet->setDirection(Vec2(-1, 0));
		tBullet->setSpeed(300);
		tBullet->setColor(Color3B::RED);
		tParts->addBullet(tBullet);
	}
	tBoss->addParts(tParts);
#pragma endregion

#pragma region Hand
	tParts = CEnemyParts::create();
	tSprite = Sprite::createWithSpriteFrameName("enemy_1_hand.png");
	tSprite->setAnchorPoint(Vec2(1, 0.5));

	tParts->setSprite(tSprite);
	tParts->setPosition(Vec2(80, -26));
	tParts->setShotInterval(0.7);
	tParts->setShotOffset(Vec2(-50, 0));
	tParts->setHP(DEFAULT_HP * 0.6);
	tParts->setZOrder(4);
	tParts->setBulletLayer(tBulletLayer);

	for (int i = 0; i < 4; i++)
	{
		tBullet = CBulletDirection::create();
		tBullet->setDirection(Vec2(-1, 0));
		tBullet->setSpeed(300);
		tBullet->setColor(Color3B::RED);
		tParts->addBullet(tBullet);
	}
	tBoss->addParts(tParts);
#pragma endregion

#pragma region Cover
	tParts = CEnemyParts::create();
	tSprite = Sprite::createWithSpriteFrameName("enemy_1_cover.png");
	tSprite->setAnchorPoint(Vec2(0, 0.5));

	tParts->setSprite(tSprite);
	tParts->setPosition(Vec2(50, 25));
	tParts->setShotInterval(0.4);
	tParts->setShotOffset(Vec2(20, 30));
	tParts->setHP(DEFAULT_HP * 1.5);
	tParts->setZOrder(7);
	tParts->setBulletLayer(tBulletLayer);

	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			tBullet = CBulletFactory::creataBullet3Way(
				DirSpeed(Vec2(-1, 0), 400),
				DirSpeed(Vec2(-1, -0.5), 500),
				DirSpeed(Vec2(-0.5, -0.95), 660)
			);
			tBullet->setColor(Color3B::RED);
			tParts->addBullet(tBullet);
		}
		else
		{
			tCurve = CBulletCurve::create();
			tCurve->setDirection(Vec2(-1, -1));
			tCurve->setSpeed(600);
			tCurve->setRadius(700);
			tCurve->setColor(Color3B::RED);
			tParts->addBullet(tCurve);
		}
	}
	tBoss->addParts(tParts);
#pragma endregion

#pragma region Baby
	tParts = CEnemyParts::create();
	tSprite = Sprite::createWithSpriteFrameName("enemy_1_baby.png");
	tSprite->setAnchorPoint(Vec2(0, 0.5));

	tParts->setSprite(tSprite);
	tParts->setPosition(Vec2(50, 42));
	tParts->setShotInterval(0.2);
	tParts->setShotOffset(Vec2(20, 30));
	tParts->setHP(DEFAULT_HP * 1.5);
	tParts->setZOrder(6);
	tParts->setBulletLayer(tBulletLayer);

	for (int i = 0; i < 20; i++)
	{
		tBullet = CBulletFactory::creataBullet3Way(
			DirSpeed(Vec2(-0.5,1),600),
			DirSpeed(Vec2(-1,0.68), 500),
			DirSpeed(Vec2(-1,0.2), 500)
		);
		tBullet->setColor(Color3B::RED);
		tParts->addBullet(tBullet);
	}
	tBoss->addParts(tParts);
#pragma endregion


	/*
	tParts = CEnemyParts::create();
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
