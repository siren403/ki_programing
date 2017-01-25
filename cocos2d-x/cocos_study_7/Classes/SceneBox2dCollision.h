#ifndef __SCENEBOX2DCOLLISION_H__
#define __SCENEBOX2DCOLLISION_H__

#include "cocos2d.h"

#include "Box2D\Box2D.h"
#include "ContectListener.h"

#include "b2Custom\GLES-Render.h"
#include <vector>


using namespace cocos2d;

#define PTM_RATIO 32

class SceneBox2DCollision : Layer
{
protected:
	Vector<Sprite *> mpSpriteVec;
	Label * mpLabelDebug = nullptr;

	b2Body * mpCurBody = nullptr;

	CustomCommand mCustomCmd;
	void onDraw(const Mat4& transform, uint32_t flags);
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

	Layer * mpLayerUI = nullptr;
	Sprite * mpSprBtn = nullptr;
	Size mWinSize;

	b2World * mpWorld = nullptr;
	ContactListener * mpContactListener = nullptr;

	void createPhysicsWorld();
	void destroyPhysicsWorld();
	void updatePhysicsWorld(float dt);

	void doFire();
	
	GLESDebugDraw * mDebugDraw;

	virtual void draw(Renderer * renderer, const Mat4& transform, uint32_t flags) override;

	Sprite * mpSpriteShooter = nullptr;
	float mTouchDistance = 0;

	std::vector<b2Body *> mBlocks;
	std::vector<b2Body *> mBullets;
	void createBlocks();
	void addNewBlock(Vec2 pos, Size size);
	b2Body * mpBodyWall = nullptr;
};

#endif // !__SCENEBOX2DCOLLISION_H__
