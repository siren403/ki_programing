#include "SceneShooter.h"
#include "b2Bullet.h"
#include "b2Block.h"
#include "b2RopeTarget.h"

#include <rapidjson\document.h>
#include <rapidjson\reader.h>

#define PI 3.14

using namespace rapidjson;
using namespace std;

struct BlockData
{
	float x;
	float y;
	float r;
};
struct StageInfo
{
	int id;
	vector<BlockData> blockList;
};

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
	mWorldSizeRatio = Vec2(1.5, 1);

	if (!b2Layer::init())
	{
		return false;
	}

	mpSpriteShooter = Sprite::create("f1.png");
	mpSpriteShooter->setAnchorPoint(Vec2(0, 0));
	mpSpriteShooter->setPosition(Vec2(100, 70));
	mpSpriteShooter->setRotation(-45);
	this->addChild(mpSpriteShooter, 1);


	string tData = FileUtils::getInstance()->getStringFromFile("data/stage.json");
	log("[%s]", tData.c_str());

	Document document;

	if (document.Parse<0>(tData.c_str()).HasParseError())
	{
		log("[%d] parse error",document.GetParseError());
		return true;
	}
	

	vector<StageInfo> tStageInfoList;

	rapidjson::Value & tDocStageInfoList = document["stage_info_list"];
	for (int i = 0; i < tDocStageInfoList.Size(); i++)
	{
		StageInfo tInfo;
		tInfo.id = tDocStageInfoList[i]["id"].GetInt();

		rapidjson::Value & tDocBlockList = tDocStageInfoList[i]["block_list"];
		for (int j = 0; j < tDocBlockList.Size(); j++)
		{
			BlockData bdata;
			bdata.x = tDocBlockList[j]["x"].GetDouble();
			bdata.y = tDocBlockList[j]["y"].GetDouble();
			bdata.r = tDocBlockList[j]["r"].GetDouble();
			tInfo.blockList.push_back(bdata);
		}
		tStageInfoList.push_back(tInfo);
	}
	
	int tStageNumber = 0;
	for (int i = 0; i < tStageInfoList[tStageNumber].blockList.size(); i++)
	{
		auto data = tStageInfoList[tStageNumber].blockList[i];
		auto tBlock = b2Block::create();
		tBlock->setPosition(mWorldSize.width * data.x, mWorldSize.height * data.y);
		tBlock->setRotation(data.r);
		this->Addb2Child(tBlock, 0);
	}

	document.RemoveAllMembers();

	this->schedule(CC_SCHEDULE_SELECTOR(SceneShooter::updateLatestBulletTrace));

	auto tRopeTarget = b2RopeTarget::create();
	tRopeTarget->setPosition(mWorldSize.width*0.3, mWorldSize.height*0.8);
	this->Addb2Child(tRopeTarget, 1);

	auto tBlock = b2Block::create();
	tBlock->setPosition(mWorldSize.width*0.3, mWorldSize.height*0.1);
	tBlock->setScale(1,0.7);
	this->Addb2Child(tBlock, 1);

	tRopeTarget->AttachTarget(tBlock);

	return true;
}

void SceneShooter::onEnter()
{
	b2Layer::onEnter();

	auto tSeq = Sequence::create(
		/*MoveTo::create(1,Vec2(-mWorldSize.width/2, 0)),
		MoveTo::create(1, Vec2(0, 0)),*/
		CallFunc::create([this]() { this->mIsShootable = true; }),
		nullptr
	);

	this->runAction(tSeq);
}

void SceneShooter::onExit()
{

	this->unscheduleAllSelectors();
	b2Layer::onExit();
}

bool SceneShooter::onTouchBegan(Touch * touch, Event * unused_event)
{
	if (mIsShootable == false)
	{
		return false;
	}

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
	tBullet->setRotation(mpSpriteShooter->getRotation());
	this->Addb2Child(tBullet, 0);

#pragma endregion

#pragma region Fire

	mTouchDistance = sqrt(pow(tdx, 2) + pow(tdy, 2));

	//방향은 각도 70도, 힘의 크기는 100의 경우를 보이고 있다.
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(mShootDegree));
	log("power : %f", mTouchDistance * 0.3f);
	double tFScalar = clampf(mTouchDistance * 0.3f, 0,150);

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

	//mIsShootable = false;
	mpLatestBullet = tBullet;
	mIsLatestBulletTrace = true;
	mpSpriteShooter->setOpacity(255*0.5f);
	this->runAction(Follow::create(tBullet, Rect(0, 0, mWorldSize.width, mWorldSize.height)));
}

void SceneShooter::CalcShootDegree(Vec2 tTouchPos)
{
	float tdx = tTouchPos.x - mpSpriteShooter->getPosition().x;
	float tdy = tTouchPos.y - mpSpriteShooter->getPosition().y;

	float tDegree = CC_RADIANS_TO_DEGREES(atan2(-tdy, tdx));
	mShootDegree = clampf(tDegree, -90, -10);
}

void SceneShooter::updateLatestBulletTrace(float dt)
{
	if (mIsLatestBulletTrace && mpLatestBullet != nullptr)
	{
		b2Vec2 tVelocity = mpLatestBullet->GetBody()->GetLinearVelocity();
		float tVelLength = tVelocity.Length();
		if (tVelLength < 0.05f)
		{
			mIsLatestBulletTrace = false;
			this->stopAllActions();
			auto tSeq = Sequence::create(
				MoveTo::create(0.5,Vec2::ZERO),
				DelayTime::create(0.3),
				CallFunc::create([this]() 
			{
				this->mIsShootable = true;
				this->mpSpriteShooter->setOpacity(255);
			}),
				nullptr
			);
			this->runAction(tSeq);
		}
	}
}
