#include "ScenePlay.h"
#include "CollisionUtils.h"
#include "StopWatch.h"
#include "Boss.h"
#include "ActorManager.h"







Scene * ScenePlay::createScene()
{
	auto scene = Scene::create();
	auto play = ScenePlay::create();

	scene->addChild(play);

	return scene;
}

bool ScenePlay::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//root
	mRenderNode = Node::create();
	this->addChild(mRenderNode, 0);


	//root->uiNode
	mUINode = Node::create();
	mRenderNode->addChild(mUINode, 10);

#pragma region Pad

	mUIPadBack = Sprite::create("ui/pad/ui_pad_back.jpg");
	mUIPadBack->setAnchorPoint(Vec2(0.5, 0));
	mUIPadBack->setPosition(Vec2(visibleSize.width*0.5, 0));
	//mUIPadBack->setScale(CC_CONTENT_SCALE_FACTOR());
	mUIPadBack->setColor(Color3B::GRAY);
	mUINode->addChild(mUIPadBack, 0);


	mUIPadFront = Sprite::create("ui/pad/ui_pad_front.png");
	Size uiPadBackSize = mUIPadBack->getContentSize();
	mUIPadFront->setPosition(Vec2(uiPadBackSize.width*0.5, uiPadBackSize.height*0.5));
	//mUIPadFront->setScale(CC_CONTENT_SCALE_FACTOR());
	mUINode->addChild(mUIPadFront, 1);

	mUIPadFrontImage = new Image();
	mUIPadFrontImage->initWithImageFile("ui/pad/ui_pad_front.png");
	mUIPadFrontImage->autorelease();
	mUIPadFrontImage->retain();


	mPadMaxDistance = 3;
#pragma endregion

	mTouchSlideTime = 0.25;
	mTouchStopWatch = StopWatch::create();
	this->addChild(mTouchStopWatch);


	//root->playNode
	mPlayNodeSize = Size(visibleSize.width, visibleSize.height - uiPadBackSize.height);
	mPlayNode = Node::create();
	mPlayNode->setPosition(Vec2(0, uiPadBackSize.height));

	mRenderNode->addChild(mPlayNode, 0);

#pragma region Map 
	
	//root->playNode->mapNode
	mMapNode = Node::create();
	mPlayNode->addChild(mMapNode, 0);


	mMapTileNames[0] = "samples/t_stone_floor.png";
	mMapTileNames[1] = "samples/t_stone_wall_left.png";
	mMapTileNames[2] = "samples/t_stone_wall_right.png";
	mMapTileNames[3] = "samples/t_stone_wall_top.png";


	float tileWidth = 18;

	mMapTiles.reserve(MAP_HEIGHT);
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		mMapTiles.pushBack(new SpriteVector(MAP_WIDTH));
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			//todo : tile Node warpping
			auto sprTile = Sprite::create(mMapTileNames[mTileSet[y][x]]);
			Vec2 pos;
			pos.x = (tileWidth*0.5) + tileWidth * x;
			pos.y = (tileWidth*0.5) + tileWidth * y;
			sprTile->setPosition(pos);
			mMapNode->addChild(sprTile, 0);

			mMapTiles.at(y)->GetSprites().pushBack(sprTile);
		}
	}

	mMapNode->setScale(2 * CC_CONTENT_SCALE_FACTOR());
	//log("content size %f", mMapTiles.at(0)->GetSprites().at(0)->getContentSize().width);
	//log("content size * scale %f", mMapTiles.at(0)->GetSprites().at(0)->getContentSize().width * mMapNode->getScale());
	mTileWidth = mMapTiles.at(0)->GetSprites().at(0)->getContentSize().width * mMapNode->getScale();


	Size mapContentSize = Size((tileWidth * MAP_WIDTH)*mMapNode->getScale(),
		(tileWidth * MAP_HEIGHT)*mMapNode->getScale());

#pragma endregion


#pragma region Player


	mPlayer = Player::create();
	mPlayer->setPosition(mapContentSize.width*0.5, mapContentSize.height*0.2);
	//mPlayer->setPosition(mapContentSize.width*0.0, mapContentSize.height*0.0);

	mPlayer->SetIsControl(true);
	mPlayer->SetMoveArea(mPlayNodeSize);
	mPlayNode->addChild(mPlayer, 1);


	mArrow = Arrow::create();
	mArrow->InitWithPlayer(mPlayer);
	mPlayNode->addChild(mArrow, mPlayer->getLocalZOrder() + 1);

	ActorManager::GetInstance()->SetPlayer(mPlayer);

	/*auto arrow = Sprite::create("samples/arrow.png");
	arrow->setPosition(mPlayer->getPosition());
	mPlayNode->addChild(arrow, 10);*/

#pragma endregion

#pragma region Enemy

	mCurrentEnemy = Boss::create();
	mCurrentEnemy->setPosition(mapContentSize.width * 0.5, mapContentSize.height * 0.55);
	mPlayNode->addChild(mCurrentEnemy, 5);

#pragma endregion


	//auto Spr = Sprite::create("CloseNormal.png");
	//Spr->setScale(0.5);
	//Spr->setPosition(360,905);
	//Spr->setGlobalZOrder(10);
	//this->addChild(Spr);

	this->scheduleUpdate();
	return true;
}

void ScenePlay::onEnter()
{
	LayerColor::onEnter();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(ScenePlay::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ScenePlay::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ScenePlay::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void ScenePlay::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	CC_SAFE_RELEASE_NULL(mUIPadFrontImage);

	LayerColor::onExit();
}

void ScenePlay::update(float dt)
{
	if (mCurrentEnemy != nullptr)
	{
		mCurrentEnemy->CheckCollisionArrow(mArrow);
	}


#pragma region Map Scroll

	Vec2 pos = mPlayer->getPosition();
	//log("%f,%f", pos.x, pos.y);

	pos.x = mPlayNodeSize.width * 0.5;
	pos.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;
	//log("%f,%f", pos.x, pos.y);

	Vec2 origin;
	origin.x = mPlayNodeSize.width * 0.5;
	origin.y = (mPlayNodeSize.height * 0.5) + mUIPadBack->getContentSize().height;

	pos = origin - mPlayer->getPosition();
	
	//log("%f,%f", pos.y, mUIPadBack->getContentSize().height);
	pos.y = MIN(pos.y, mUIPadBack->getContentSize().height);
	mPlayNode->setPosition(pos);

#pragma endregion

#pragma region MapTileSearch

	int x;
	int y;
	x = mPlayer->getPosition().x / mTileWidth;
	y = mPlayer->getPosition().y / mTileWidth;
	x = ClampI(x, 0, MAP_WIDTH - 1);
	y = ClampI(y, 0, MAP_HEIGHT - 1);
	auto tile = mMapTiles.at(y)->GetSprites().at(x);
	if (tile->getColor() != Color3B::RED)
	{
		tile->setColor(Color3B::RED);
	}

	

	x = mArrow->getPosition().x / mTileWidth;
	y = mArrow->getPosition().y / mTileWidth;
	x = ClampI(x, 0, MAP_WIDTH - 1);
	y = ClampI(y, 0, MAP_HEIGHT - 1);
	tile = mMapTiles.at(y)->GetSprites().at(x);
	if (tile->getColor() != Color3B::GREEN)
	{
		tile->setColor(Color3B::GREEN);
	}

	if (mArrow->GetState() == Arrow::State::State_Shot)
	{
		Vec2 dir = mArrow->GetMoveDirection();
		dir.x = dir.x > 0 ? 1 : dir.x < 0 ? -1 : 0;
		dir.y = dir.y > 0 ? 1 : dir.y < 0 ? -1 : 0;

		if (dir.x != 0)
		{
			int dx = ClampI(x + dir.x, 0, MAP_WIDTH - 1);
			if (mTileSet[y][dx] != 0 &&
				utils::getCascadeBoundingBox(mMapTiles.at(y)->GetSprites().at(dx))
				.intersectsRect(utils::getCascadeBoundingBox(mArrow)))//바닥이 아니고 바닥이 아닌 스프라이트와 화살이 충돌 했는지
			{
				log("collision tile dx");
				mArrow->OnCollisionOther(true , mMapTiles.at(y)->GetSprites().at(dx));
				return;
			}
		}
		if (dir.y != 0)
		{
			int dy = ClampI(y + dir.y, 0, MAP_HEIGHT - 1);
			if (mTileSet[dy][x] != 0 &&
				utils::getCascadeBoundingBox(mMapTiles.at(dy)->GetSprites().at(x))
				.intersectsRect(utils::getCascadeBoundingBox(mArrow)))//바닥이 아니고 바닥이 아닌 스프라이트와 화살이 충돌 했는지
			{
				log("collision tile dy");
				mArrow->OnCollisionOther(true, mMapTiles.at(dy)->GetSprites().at(x));
				return;
			}
		}
		/*log("current point %d,%d", x, y);
		x += dir.x;
		y += dir.y;
		log("next point %d,%d", x, y);*/
	}

	//mArrow->OnCollisionOther(mTileSet[y][x] != 0, mMapTiles.at(y)->GetSprites().at(x));

#pragma endregion
}

bool ScenePlay::onTouchBegan(Touch * touch, Event * unused_event)
{
	bool isTouchMoved = false;
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());
	if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
	{
		if (mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
			CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos))//move
		{
			//mTouchBeganPos = touch->getLocation();
			mTouchBeganPos = convertToWorldSpace(mUIPadFront->getPosition());
			mTouchState = TouchState::Move;
			mTouchStopWatch->OnStart();
			isTouchMoved = true;
		}
		else if(mArrow->GetState() != Arrow::State::State_Drop)//attack
		{
			mTouchBeganPos = touch->getLocation();
			mTouchState = TouchState::Shot;

			Vec2 dir = mTouchBeganPos - convertToWorldSpace(mUIPadFront->getPosition());
			mArrow->LockOn(dir.getNormalized());
			isTouchMoved = true;
		}
		else//ArrowDrop...
		{
			mArrow->SetReturnArrow(true);
			mTouchState = TouchState::Collect;
			isTouchMoved = true;
		}
		//isTouchMoved = true;
	}


	return isTouchMoved;
}

void ScenePlay::onTouchMoved(Touch * touch, Event * unused_event)
{
	Vec2 touchPos = touch->getLocation();
	touchPos.clamp(Vec2::ZERO, mUIPadBack->getContentSize());
	Vec2 dir;

	switch (mTouchState)
	{
	case TouchState::Move:
		dir = touchPos - mTouchBeganPos;

		//log("%f,%f", dir.x, dir.y);

		dir.x = clampf(dir.x / 60, -1, 1);
		dir.y = clampf(dir.y / 60, -1, 1);

		mPlayer->SetMoveDir(dir);

		//mArrow->LockOn(atan2(dir.y, dir.x));
		mArrow->LockOn(dir.getNormalized());

		//log("%f", atan2(dir.y, dir.x));
		break;
	case TouchState::Shot:
		dir = mTouchBeganPos - touchPos;
		//mArrow->LockOn(atan2(dir.y, dir.x));
		mArrow->LockOn(dir.getNormalized());

		break;
	}
}

void ScenePlay::onTouchEnded(Touch * touch, Event * unused_event)
{
	auto touchPos = mUINode->convertToNodeSpace(touch->getLocation());

	switch (mTouchState)
	{
	case TouchState::Shot:
		mArrow->Shot();
		break;
	case TouchState::Move:
		if (mUIPadBack->getBoundingBox().containsPoint(touchPos))
		{
			if (!(mUIPadFront->getBoundingBox().containsPoint(touchPos) &&
				CollisionUtils::GetInst()->ContainsPointToPixel(mUIPadFront, mUIPadFrontImage, touchPos)))//move
			{
				Vec2 dir = touch->getLocation() - mTouchBeganPos;
				float endedRadian = atan2(dir.y, dir.x);
				mPlayer->OnRoll(endedRadian);
			}
		}
		mArrow->DisableLockOn();
		break;
	case TouchState::Collect:
		mArrow->SetReturnArrow(false);
		break;
	}


	/*float touchTime = mTouchStopWatch->OnStop();

	if (touchTime > mTouchSlideTime)
	{
		mPlayer->SetMoveDir(Vec2::ZERO);
	}
	else
	{
		Vec2 pos = touch->getLocation() - mTouchBeganPos;
		float endedRadian = atan2(pos.y, pos.x);
		mPlayer->OnRoll(endedRadian);
	}*/

	mTouchState = TouchState::None;
	mPlayer->SetMoveDir(Vec2::ZERO);

}

int ScenePlay::ClampI(int value, int min, int max)
{
	return value < min ? min : value>max ? max : value;
}