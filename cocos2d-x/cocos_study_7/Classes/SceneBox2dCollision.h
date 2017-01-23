#ifndef __SCENEBOX2DCOLLISION_H__
#define __SCENEBOX2DCOLLISION_H__

#include "cocos2d.h"

#include "Box2D\Box2D.h"
#include "ContectListener.h"

#include <GLES-Render.h>
#include <vector>


using namespace cocos2d;

#define PTM_RATIO 32

class SceneBox2DCollision : Layer
{
protected:
	Vector<Sprite *> mpSpriteVec;
	Label * mpLabelDebug = nullptr;

	b2Body * mpCurBody = nullptr;

public:
	static Scene * createScene();

	virtual bool init() override;
	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

	CREATE_FUNC(SceneBox2DCollision);

public:
	Layer * mpLayerUI;
	Sprite * mpSprBtn = nullptr;
	Size mWinSize;

	b2World * mpWorld = nullptr;
	ContactListener * mpContactListener = nullptr;

	void createPhysicsWorld();
	void destroyPhysicsWorld();
	void updatePhysicsWorld(float dt);

	void doFire();
protected:
	CustomCommand mCustomCmd;
	void onDraw(const Mat4& transform, uint32_t flags);

public:
	GLESDebugDraw * mDebugDraw;

	virtual void draw(Renderer * renderer, const Mat4& transform, uint32_t flags) override;

};

#endif // !__SCENEBOX2DCOLLISION_H__
