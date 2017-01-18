#ifndef __SOUNDMGR_H__
#define __SOUNDMGR_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class SoundMgr
{
private:
	static SoundMgr * mpInstance;

	SoundMgr();
	~SoundMgr();

	string mStringBGArray[1] = { "" };
	string mStringEffectArray[1] = { "" };
public:
	static SoundMgr * getInstance();

	void create();
	void destroy();



	void playBGM(int tIndex, bool tIsLoop = true);
	void stopBGM();


	void playEffect(int tIndex);
	void stopAllEffects();

};

#endif // !__SOUNDMGR_H__
