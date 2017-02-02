#include "SceneBPMTest.h"
#include "BPMPlayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene * SceneBPMTest::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneBPMTest::create();
	scene->addChild(layer);
	
	return scene;
}

bool SceneBPMTest::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	mBPMPlayer = BPMPlayer::create();
	mBPMPlayer->SetCallBackBPM(CC_CALLBACK_1(SceneBPMTest::ReceiveBPM, this));
	mBPMPlayer->SetBPM(129);
	this->addChild(mBPMPlayer);


	auto tAudio = SimpleAudioEngine::getInstance();
	tAudio->setEffectsVolume(1);
	tAudio->setBackgroundMusicVolume(1.0f);
	tAudio->preloadEffect(mSEName);
	tAudio->preloadBackgroundMusic(mBGMName);


	auto tKeyListener = EventListenerKeyboard::create();
	tKeyListener->onKeyPressed = CC_CALLBACK_2(SceneBPMTest::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tKeyListener, this);

	/*auto Seq = Sequence::create(
		DelayTime::create(1),
		CallFunc::create(CC_CALLBACK_0(BPMPlayer::Start, mBPMPlayer)),
		nullptr
	);

	this->runAction(Seq);*/

	return true;
}

void SceneBPMTest::onKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (mIsPlaying == false)
		{
			mBPMPlayer->Start();
			SimpleAudioEngine::getInstance()->playBackgroundMusic(mBGMName);
		}
		else
		{
			mBPMPlayer->Stop();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
		mIsPlaying = !mIsPlaying;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		SimpleAudioEngine::getInstance()->playEffect(mSEName);
		break;
	}
}

void SceneBPMTest::ReceiveBPM(int tempo)
{
	static bool tempoStart = false;
	if (tempo == 6)
	{
		tempoStart = true;
	}
	if (tempoStart)
	{
		log("tempo:%d", tempo);
		/*SimpleAudioEngine::getInstance()->unloadEffect(mSEName);
		SimpleAudioEngine::getInstance()->playEffect(mSEName);*/
	}
}



