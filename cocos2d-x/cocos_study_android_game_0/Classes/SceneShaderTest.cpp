#include "SceneShaderTest.h"

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

	auto sprite = Sprite::create("samples/bloom.png");
	sprite->setPosition(centerPos);
	sprite->setScale(2);
	this->addChild(sprite);

	std::string vsh = "shader/ccPositionTextureColor_noMVP_vert.vsh";
	std::string fsh = "shader/test/bloomTest.fsh";
	//fsh = "shader/test/circles.fsh";
	auto glProgram = GLProgram::createWithFilenames(vsh, fsh);
	mGLState = GLProgramState::getOrCreateWithGLProgram(glProgram);
	sprite->setGLProgramState(mGLState); 


	mGLState->setUniformVec3("changeColor", Vec3(0.5, 0.7, 0.2));
	mGLState->setUniformVec3("pointColor", Vec3(1, 0, 1));

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

	mGLState->setUniformFloat("colorRatio", sin(mCurrentTime));
}
