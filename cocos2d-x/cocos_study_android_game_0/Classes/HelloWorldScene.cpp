#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define ZORDER_POST_EFFECT 100

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
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    
	

	auto tWinSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mpRenderNode = Node::create();
	this->addChild(mpRenderNode, 1);

	auto tBackSprite = Sprite::create("image/background3.jpg");
	tBackSprite->setScaleX(2.7);
	tBackSprite->setScaleY(2.25);
	tBackSprite->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
	mpRenderNode->addChild(tBackSprite, 0);

	mpSpritesNode = Node::create();
	mpRenderNode->addChild(mpSpritesNode);

	auto tSprite = Sprite::create("HelloWorld.png");
	tSprite->setPosition(visibleSize.width *0.5, visibleSize.height  *0.5);
	mpSpritesNode->addChild(tSprite, 1);

	tSprite = Sprite::create("HelloWorld.png");
	tSprite->setPosition(visibleSize.width *0.4, visibleSize.height  *0.4);
	mpSpritesNode->addChild(tSprite, 1);

	tSprite = Sprite::create("HelloWorld.png");
	tSprite->setPosition(visibleSize.width  *0.6, visibleSize.height  *0.4);
	mpSpritesNode->addChild(tSprite, 1);


	mpRenderTexture = RenderTexture::create(tWinSize.width, tWinSize.height, Texture2D::PixelFormat::RGBA8888);
	mpRenderTexture->retain();
	//mpRenderTexture->setScale(0.5);
	//mpRenderTexture->setGlobalZOrder(ZORDER_POST_EFFECT);
	//this->addChild(mpRenderTexture, 100);

	std::string tNoMVPVert = "shader/ccPositionTextureColor_noMVP_vert.vsh";
	mpGLProgram = GLProgram::createWithFilenames(tNoMVPVert, "shader/post_effect/lerp_color.fsh");
	mpGLState = GLProgramState::create(mpGLProgram);
	

	mpRenderSprite = Sprite::createWithTexture(mpRenderTexture->getSprite()->getTexture());
	mpRenderSprite->setAnchorPoint(Vec2(0, 0));
	mpRenderSprite->setPosition(visibleSize.width * 0.0, visibleSize.height * 0.0);
	mpRenderSprite->setScale(0.5);
	mpRenderSprite->setFlippedY(true);
	mpRenderSprite->setGLProgramState(mpGLState);
	this->addChild(mpRenderSprite, 100);
	
	mpRenderSprite = Sprite::createWithTexture(mpRenderTexture->getSprite()->getTexture());
	mpRenderSprite->setAnchorPoint(Vec2(0, 0));
	mpRenderSprite->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5);
	mpRenderSprite->setScale(0.5);
	mpRenderSprite->setFlippedY(true);
	mpRenderSprite->setGLProgramState(mpGLState);
	this->addChild(mpRenderSprite, 100);


	mpGLState->setUniformVec3("u_lerpColor", Vec3(0.7, 0.7, 0.7));
	mpGLState->setUniformVec2("u_resolution", mpRenderSprite->getContentSize());
	mpGLState->setUniformVec4("u_outLineColor", Vec4(0.7, 0.7, 0.7, 0.5));
	mpGLState->setUniformFloat("u_outLineThickness", mpRenderSprite->getContentSize().width * 0.05);
	mpGLState->setUniformFloat("u_blend", 0.9);
	mpGLState->setUniformCallback("u_blend", []
	(GLProgram * tGLProg, Uniform * tUniform)
	{
		static float blend = 0;
		static float db = 0.01;
		blend += db;
		if (0 > blend || blend > 1)
		{
			db = -db;
		}
		log("%f", blend);
		tGLProg->setUniformLocationWith1f(tUniform->location, blend);
	});

	//mpRenderTexture->setGLProgramState(mpGLState);


	auto tSeq = Sequence::create(
		MoveBy::create(1,Vec2(100,0)),
		CallFunc::create([this]()
	{
		//this->mpRenderTexture->setVisible(false);
	}),
		DelayTime::create(0.0),
		CallFunc::create([this]() 
	{
		//this->mpRenderTexture->setColor(Color3B::RED);
		//this->mpRenderTexture->setVisible(true);
	}),
		MoveBy::create(1, Vec2(-100, 0)),
		nullptr
	);
	auto tRepeat = RepeatForever::create(tSeq);
	mpSpritesNode->runAction(tRepeat);

	this->scheduleUpdate();


    return true;
}

void HelloWorld::onEnter()
{
	LayerColor::onEnter();
}

void HelloWorld::onExit()
{
	mpRenderTexture->release();
	LayerColor::onExit();
}

void HelloWorld::update(float dt)
{
	mpRenderTexture->beginWithClear(0,0,0,0);
	//this->visit();
	//mpRenderSprite->visit();
	mpRenderNode->visit();
	mpRenderTexture->end();
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

