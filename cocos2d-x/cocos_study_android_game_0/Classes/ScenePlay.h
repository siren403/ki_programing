#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "Arrow.h"
#include <map>

using namespace cocos2d;
using namespace std;

#define MAP_WIDTH 30
#define MAP_HEIGHT 25

class Enemy;
class MapTileVector;
class PlayMap;
class Player;
class StopWatch;

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
	Node * mMapNode = nullptr;//PlayNode 하위의 타일맵 노드

	Size mPlayNodeSize;
	Vec2 mPlayNodeOffsetDirection;
	float mPlayNodeOffsetScalar = 0;

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
	StopWatch * mRollStopWatch = nullptr;

	//Map
	PlayMap * mPlayMap;

	//Enemy
	Enemy * mCurrentEnemy = nullptr;

	//GameState
	int mCurrentRoomIndex = 0;
	bool mIsPlaying = false;
	Node * mCameraTarget = nullptr;
	Actor * mCameraSecondTarget = nullptr;
	float mFollowRatio = 0;
	bool mIsCameraShake = false;
	StopWatch * mShakeStopWatch = nullptr;

	//Screen
	Sprite * mFadeSprite = nullptr;

	void RoomSequence(int roomIndex, bool isReset = false);
	void CalculatePlayNodePosition(float dt);

	void GameOverSequence();
	void RoomClearSequence();
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
	