#include "EffectEnemyKill.h"

bool EffectEnemyKill::init()
{
	if (!Node::init())
	{
		return false;
	}

	mLineAnchor = Vec2(0.25f, 0.5f);
	mLineColor = Color3B(247, 87, 82);
	mLineRect = Rect(0, 0, 256, 20);
	mLineAngle = 2.0f;

	mLine_0 = Sprite::create("white4x4.jpg");
	mLine_0->setScaleX(0);
	mLine_0->setAnchorPoint(mLineAnchor);
	mLine_0->setColor(mLineColor);
	mLine_0->setTextureRect(mLineRect);
	mLine_0->setRotation(-mLineAngle);
	this->addChild(mLine_0);
	mLine_1 = Sprite::create("white4x4.jpg");
	mLine_1->setScaleX(0);
	mLine_1->setAnchorPoint(mLineAnchor);
	mLine_1->setColor(mLineColor);
	mLine_1->setTextureRect(mLineRect);
	mLine_1->setRotation(mLineAngle);
	this->addChild(mLine_1);


	return true;
}

FiniteTimeAction * EffectEnemyKill::CreateAction(Vec2 playerPos, Vec2 enemyPos)
{

	Vec2 dir = enemyPos - playerPos;

	this->setPosition(enemyPos);
	this->setRotation(CC_RADIANS_TO_DEGREES(atan2(-dir.y, dir.x)));

	auto seq = Sequence::create(
		CallFunc::create([this]()
	{
		auto scale = EaseExponentialOut::create(ScaleTo::create(0.25f, 3, 1));
		mLine_0->runAction(Spawn::create(
			scale,
			EaseExponentialOut::create(RotateBy::create(0.3f, -25.0f)),
			nullptr));
		mLine_1->runAction(Spawn::create(
			scale->clone(),
			EaseExponentialOut::create(RotateBy::create(0.3f, 25.0f)),
			nullptr));
	}),
		DelayTime::create(0.18f),
		CallFunc::create([this]()
	{
		mLine_0->runAction(EaseCubicActionOut::create(ScaleTo::create(0.12f, 3, 0)));
		mLine_1->runAction(EaseCubicActionOut::create(ScaleTo::create(0.12f, 3, 0)));
	}),
		DelayTime::create(0.12f),
		CallFunc::create([this]()
	{
		mLine_0->setScaleX(0);
		mLine_0->setRotation(-mLineAngle);
		mLine_1->setScaleX(0);
		mLine_1->setRotation(mLineAngle);
	}),
		nullptr);
	//effect->runAction(RepeatForever::create(seq));
	return seq;
}

void EffectEnemyKill::Show(Vec2 playerPos, Vec2 enemyPos)
{
	this->runAction(this->CreateAction(playerPos, enemyPos));
}
