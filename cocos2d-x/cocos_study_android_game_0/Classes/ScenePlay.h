#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"
#include "Player.h"
#include "Arrow.h"

#pragma execution_character_set("utf-8")

using namespace cocos2d;

class StopWatch;
class Enemy;

enum TouchState
{
	None = 0,
	Move = 1,
	Shot = 2,
	Collect = 3,
};

class ScenePlay : public LayerColor
{
private:
	//레이어 구분
	Node * mRenderNode = nullptr;//this 다음으로 최상위 노드
	Node * mUINode = nullptr;//RenderNode에 속하는 UI부분 노드 ex) 컨트롤러,...
	Node * mPlayNode = nullptr;//UI노드와 같은 레벨의 플레이 부분 노드, ex) 맵,플레이어,적,...

	//player
	Player * mPlayer = nullptr;
	Arrow * mArrow = nullptr;


	//ui
	Sprite * mUIPadBack = nullptr;
	Sprite * mUIPadFront = nullptr;
	Image * mUIPadFrontImage = nullptr;

	//input
	float mPadMaxDistance;
	Vec2 mTouchBeganPos;
	TouchState mTouchState = TouchState::None;
	StopWatch * mTouchStopWatch = nullptr;
	float mTouchSlideTime;

	Size mPlayNodeSize;

	Enemy * mCurrentEnemy = nullptr;
public:
	static Scene * createScene();
	CREATE_FUNC(ScenePlay);

	//라이프 사이클 오버라이드
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;

	//Input 인터페이스 오버라이드
	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

};

#endif // !__SCENEPLAY_H__
