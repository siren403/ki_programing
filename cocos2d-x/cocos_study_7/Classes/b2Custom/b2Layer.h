#ifndef __B2LAYER_H__
#define __B2LAYER_H__

#include "cocos2d.h"
#include "b2Node.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

class b2Layer : public Layer
{
private:
	GLESDebugDraw * mpDebugDraw = nullptr;
protected:
	b2World * mpWorld = nullptr;
	bool mIsDebug = false;
	b2Vec2 mGravity;
	Size mWinSize;
	Vec2 mWorldSizeRatio;
	Size mWorldSize;
	float mWorldBoxMargin = 0;

	virtual void AddTouchListener();
	virtual void updatePhysics(float dt);
public:
	static Scene * createScene();
	CREATE_FUNC(b2Layer);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	void draw(Renderer * renderer, const Mat4 & transform, uint32_t flags) override;

	void Addb2Child(b2Node * node);
	void Addb2Child(b2Node * node,int localZorder);

};

#endif // !__B2LAYER_H__
