#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Glow.h"
#include "ShaderTest.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(
		Color4B::WHITE
	))
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto tCenter = Vec2(visibleSize.width*0.5, visibleSize.height*0.5);
	
	//auto tGlow = Glow::create();
	//tGlow->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(tGlow, 1);



	auto tShaderTest = ShaderTest::create();
	this->addChild(tShaderTest);



	/*sprite = Sprite::create("HelloWorld.png");
	sprite->setAnchorPoint(Vec2(0, 0.5));
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y));

	glprogram = GLProgram::createWithFilenames("blur.vsh", "blur.fsh");
	glProgramState = GLProgramState::getOrCreateWithGLProgram(glprogram);
	glProgramState->setUniformVec2("u_stepSize", Vec2(1, 1));

	sprite->setGLProgramState(glProgramState);

	this->addChild(sprite, 1);*/



    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
