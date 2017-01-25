#include "SceneShooter.h"
#include "b2Bullet.h"
#include "b2Block.h"

#define PI 3.14

Scene * SceneShooter::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneShooter::create();
	scene->addChild(layer);
	return scene;
}

bool SceneShooter::init()
{
	mGravity = b2Vec2(0, -30.0f);
	mWorldBoxMargin = 10;
	if (!b2Layer::init())
	{
		return false;
	}

	mpSpriteShooter = Sprite::create("f1.png");
	mpSpriteShooter->setAnchorPoint(Vec2(0, 0));
	mpSpriteShooter->setPosition(Vec2(100, 70));
	mpSpriteShooter->setRotation(-45);
	this->addChild(mpSpriteShooter, 1);


	auto tBlock = b2Block::create();
	tBlock->setPosition(mWinSize.width * 0.65, mWinSize.height * 0.1);
	this->Addb2Child(tBlock, 0);

	tBlock = b2Block::create();
	tBlock->setPosition(mWinSize.width * 0.85, mWinSize.height * 0.1);
	this->Addb2Child(tBlock, 0);

	tBlock = b2Block::create();
	tBlock->setPosition(mWinSize.width * 0.75, mWinSize.height * 0.3);
	tBlock->setRotation(90);
	this->Addb2Child(tBlock, 0);

	return true;
}

void SceneShooter::onEnter()
{
	b2Layer::onEnter();

	
}

void SceneShooter::onExit()
{


	b2Layer::onExit();
}

bool SceneShooter::onTouchBegan(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	CalcShootDegree(tTouchPos);
	mpSpriteShooter->setRotation(mShootDegree);

	return true;
}

void SceneShooter::onTouchMoved(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	CalcShootDegree(tTouchPos);
	mpSpriteShooter->setRotation(mShootDegree);
}

void SceneShooter::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	float tdx = tTouchPos.x - mpSpriteShooter->getPosition().x;
	float tdy = tTouchPos.y - mpSpriteShooter->getPosition().y;

#pragma region Create Bullet

	b2Bullet * tBullet = b2Bullet::create();

	//Vec2 tCreatPos = Vec2(mpSpriteShooter->getPosition().x +mpSpriteShooter->getContentSize().width,
		//mpSpriteShooter->getPosition().y + mpSpriteShooter->getContentSize().height);
	
	Vec2 tCreatPos = mpSpriteShooter->getPosition();
	float tWidth = mpSpriteShooter->getContentSize().width;
	float tRadian = clampf(atan2(tdy, tdx), PI * 0.1, PI * 0.5);
	tCreatPos.x += cos(tRadian) * tWidth;
	tCreatPos.y += sin(tRadian) * tWidth;
	

	tBullet->setPosition(tCreatPos);
	this->Addb2Child(tBullet, 0);

#pragma endregion

#pragma region Fire

	mTouchDistance = sqrt(pow(tdx, 2) + pow(tdy, 2));

	//방향은 각도 70도, 힘의 크기는 100의 경우를 보이고 있다.
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(mShootDegree));
	double tFScalar = clampf(mTouchDistance * 0.3f, 0,200);

	//닮은 삼각형임을 이용하여 각 축의 힘의 크기를 구하였다.
	double tFX = tFScalar / sqrt((tTrigonoV*tTrigonoV + 1));
	double tFY = sqrt(
		tFScalar * tFScalar -
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))*
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))
	);


	//주어진 벡터만큼의 힘을 가하는 코드이다.
	tBullet->GetBody()->ApplyLinearImpulse(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);

#pragma endregion
}

void SceneShooter::CalcShootDegree(Vec2 tTouchPos)
{
	float tdx = tTouchPos.x - mpSpriteShooter->getPosition().x;
	float tdy = tTouchPos.y - mpSpriteShooter->getPosition().y;

	float tDegree = CC_RADIANS_TO_DEGREES(atan2(-tdy, tdx));
	mShootDegree = clampf(tDegree, -90, -10);
}
