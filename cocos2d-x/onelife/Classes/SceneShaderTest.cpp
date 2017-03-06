#include "SceneShaderTest.h"
#include "ShaderWrapper.h"
#include "SWDrawCircle.h"
#include "SWDrawArc.h"
#include "EasingFunc.h"
#include "ColorUtil.h"

#define PI 3.14159

Scene * SceneShaderTest::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneShaderTest::create();
	scene->addChild(layer);
	return scene;
}

bool SceneShaderTest::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//auto sprite = Sprite::create("samples/bloom.png");
	//sprite->setPosition(centerPos);
	//sprite->setScale(2);
	//this->addChild(sprite);
	//std::string vsh = "shader/ccPositionTextureColor_noMVP_vert.vsh";
	//std::string fsh = "shader/test/bloomTest.fsh";
	////fsh = "shader/test/circles.fsh";
	//auto glProgram = GLProgram::createWithFilenames(vsh, fsh);
	//mGLState = GLProgramState::getOrCreateWithGLProgram(glProgram);
	//sprite->setGLProgramState(mGLState); 
	//mGLState->setUniformVec3("changeColor", Vec3(0.5, 0.7, 0.2));
	//mGLState->setUniformVec3("pointColor", Vec3(1, 0, 1));

#pragma region circle test

	mDrawCircle = new SWDrawCircle();
	mDrawCircle->GetSprite()->setPosition(centerPos);
	mDrawCircle->GetSprite()->setColor(Color3B::GRAY);
	auto spawn = Spawn::create(
		CallFunc::create([this]()
	{
		mDrawCircle->SetInline(1);
		mDrawCircle->SetCircleSize(0);
	}),
		EaseExponentialInOut::create(
			ActionFloat::create(0.6f, 0, 1, CC_CALLBACK_1(SWDrawCircle::SetCircleSize, mDrawCircle))),
		Sequence::create(
			DelayTime::create(0.15f),
			EaseQuarticActionIn::create(
				ActionFloat::create(0.45f, 1, 0, CC_CALLBACK_1(SWDrawCircle::SetInline, mDrawCircle))),
			nullptr),
		nullptr);
	this->runAction(RepeatForever::create(spawn));
	//this->addChild(mDrawCircle->GetSprite());
#pragma endregion

	Vec2 dir = centerPos - Vec2(visibleSize.width * 0.2f, visibleSize.height * 0.2f);

	Node * effect = Node::create();
	effect->setPosition(centerPos);
	effect->setRotation(CC_RADIANS_TO_DEGREES(atan2(-dir.y, dir.x)));
	this->addChild(effect);

	Vec2 anchor = Vec2(0.12f, 0.5f);
	Color3B color = Color3B(247, 87, 82);
	Rect rect = Rect(0, 0, 256, 20);
	float angle = 2.0f;

	Sprite * line_1 = Sprite::create("white4x4.jpg");
	line_1->setScaleX(0);
	line_1->setAnchorPoint(anchor);
	line_1->setColor(color);
	line_1->setTextureRect(rect);
	line_1->setRotation(-angle);
	effect->addChild(line_1);
	Sprite * line_2 = Sprite::create("white4x4.jpg");
	line_2->setScaleX(0);
	line_2->setAnchorPoint(anchor);
	line_2->setColor(color);
	line_2->setTextureRect(rect);
	line_2->setRotation(angle);
	effect->addChild(line_2);


	

	auto seq = Sequence::create(
		CallFunc::create([line_1,line_2]() 
	{
		auto scale = EaseExponentialOut::create(ScaleTo::create(0.25f, 3, 1));
		line_1->runAction(Spawn::create(
			scale,
			EaseExponentialOut::create(RotateBy::create(0.3f, -40.0f)),
			nullptr));
		line_2->runAction(Spawn::create(
			scale->clone(),
			EaseExponentialOut::create(RotateBy::create(0.3f, 40.0f)),
			nullptr));
	}),
		DelayTime::create(0.18f),
		CallFunc::create([line_1, line_2]()
	{
		line_1->runAction(EaseCubicActionOut::create(ScaleTo::create(0.12f, 3, 0)));
		line_2->runAction(EaseCubicActionOut::create(ScaleTo::create(0.12f, 3, 0)));
	}),
		DelayTime::create(0.12f),
		CallFunc::create([line_1, line_2,angle]()
	{
		line_1->setScaleX(0);
		line_1->setRotation(-angle);
		line_2->setScaleX(0);
		line_2->setRotation(angle);

	}),
		nullptr);
	effect->runAction(RepeatForever::create(seq));


	this->scheduleUpdate();
	return true;
}

void SceneShaderTest::update(float dt)
{
	mCurrentTime += dt;
	if (mCurrentTime >= PI)
	{
		mCurrentTime = 0;
	}
	//log("%f",sin(mCurrentTime));

	//mGLState->setUniformFloat("colorRatio", sin(mCurrentTime));

	//mDrawCircle->SetCircleSize(1.0f);
	//mDrawCircle->SetCircleSize(EasingFunc::EaseExpoInOut(mCurrentTime, 0, 1, PI));
	//mDrawCircle->SetInline(0.1);
	//mDrawCircle->SetInline(EasingFunc::EaseExpoInOut(mCurrentTime, 1, -1, PI));

}

void SceneShaderTest::onExit()
{
	LayerColor::onExit();

	CC_SAFE_DELETE(mDrawCircle);
	CC_SAFE_DELETE(mDrawArc);
}
