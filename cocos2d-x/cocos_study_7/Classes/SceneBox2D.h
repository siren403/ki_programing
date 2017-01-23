#ifndef __SCENEBOX2D_H__
#define __SCENEBOX2D_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>

using namespace cocos2d;

#define PTM_RATIO 32

class SceneBox2D : public Layer
{
protected:
	Layer * mpLayer_0 = nullptr;
	Layer * mpLayer_1 = nullptr;

	Vector<Sprite *> mSpriteVec;

	Label * mplblDebug = nullptr;

	EventListenerTouchOneByOne * mpListener = nullptr;

	Size mWinSize;
	b2World * mpb2World = nullptr;

public:
	static Scene * createScene();

	virtual bool init();
	virtual void update(float dt);

	void updateTick(float dt);

	int doRandom();

	void menuCloseCallback(Ref * pSender);

	void onClickBtnGoMove(Ref * pSender);

	//터치의 시작(손가락을 댄다), 터치한 상태로 움직이는 것, 터치의 끝(손가락을 뗀다)
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);


	// implement the "static create()" method manually
	CREATE_FUNC(SceneBox2D);

	GLESDebugDraw * m_debugDraw;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // !__SCENEBOX2D_H__
