#include "SoundMgr.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

SoundMgr * SoundMgr::mpInstance = nullptr;
 
SoundMgr::SoundMgr()
{
}
SoundMgr::~SoundMgr()
{
}

SoundMgr * SoundMgr::getInstance()
{
	if (nullptr == mpInstance)
	{
		mpInstance = new SoundMgr();
	}
	return mpInstance;
}

void SoundMgr::create()
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	mStringBGArray[0] = "Sounds/background.mp3";
	mStringEffectArray[0] = "Sounds/effect1.wav";

	int ti = 0;
	int tCount = 0;

	tCount = 1;
	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
			mStringBGArray[ti].c_str()
		);
	}

	tCount = 1;
	for (ti = 0; ti < tCount; ti++)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(
			mStringEffectArray[ti].c_str()
		);
	}

}

void SoundMgr::destroy()
{
	SimpleAudioEngine::getInstance()->unloadEffect(mStringEffectArray[0].c_str());

	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::end();
}

void SoundMgr::playBGM(int tIndex, bool tIsLoop)
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic(
		mStringBGArray[tIndex].c_str(),
		tIsLoop	
	);
}

void SoundMgr::stopBGM()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundMgr::playEffect(int tIndex)
{
	SimpleAudioEngine::getInstance()->playEffect(mStringEffectArray[tIndex].c_str());
}

void SoundMgr::stopAllEffects()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}
