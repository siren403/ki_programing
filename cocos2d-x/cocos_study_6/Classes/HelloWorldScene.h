#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
private:
	float mScrollSpeed = 0;
	Vec2 mVecA;
	Vec2 mVecB;

	Sprite * mSpriteA = nullptr;
	Sprite * mSpriteB = nullptr;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	virtual void onExit();

	unsigned int m_nSoundId;

	void doSoundAction(Ref* pSender);

	virtual void update(float dt) override;
};

#endif // __HELLOWORLD_SCENE_H__
