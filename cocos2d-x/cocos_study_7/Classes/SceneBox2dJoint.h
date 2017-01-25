#ifndef __SCENEBOX2DJOINT_H__
#define __SCENEBOX2DJOINT_H__

#include "cocos2d.h"

#include "Box2D\Box2D.h"
#include "ContectListener.h"

#include "b2Custom\GLES-Render.h"

#include <vector>


using namespace cocos2d;

#define PTM_RATIO 32

class SceneBox2dJoint : Layer
{
public:
	static Scene * createScene();

	virtual bool init() override;
	virtual void update(float dt) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

	CREATE_FUNC(SceneBox2dJoint);

	Size mWinSize;

	b2World * mpWorld = nullptr;
	ContactListener * mpContactListener = nullptr;

	void createPhysicsWorld();
	void destroyPhysicsWorld();
	void updatePhysicsWorld(float dt);

	GLESDebugDraw * mDebugDraw;
	virtual void draw(Renderer * renderer, const Mat4& transform, uint32_t flags) override;
	//============================= joint
public:
	b2Body* addNewSprite(Point point, Size size, b2BodyType bodytype, const char* spriteName, int type);
	b2Body* getBodyAtTab(Point p);
	Texture2D* texture;
	bool bDrag;
	b2Body *dragBody;
	b2MouseJoint *mpMouseJoint;
	b2Body *gbody;

protected:
	CustomCommand mCustomCmd;
	void onDraw(const Mat4& transform, uint32_t flags);



};

#endif // !__SCENEBOX2DJOINT_H__
