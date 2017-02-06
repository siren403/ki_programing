#ifndef __SPRITEANIMATOR_H__
#define __SPRITEANIMATOR_H__

#include "cocos2d.h"

using namespace cocos2d;

class SpriteAnimator : public Node
{
private:
	Sprite * mpSprite = nullptr;
	std::string mAniFileName = "";

	int mStartFrame = 0;
	int mEndFrame = 0;
	float mDelayTime = 0.0f;

	Action * mpRepeat = nullptr;
	
	void CreateAnimation();
public:
	static SpriteAnimator * Create(
		const std::string& tAniFileName,
		int tStartFrame,
		int tEndFrame,
		float tDelayTime
	);

	CREATE_FUNC(SpriteAnimator);
	
	void RunAni();
	void StopAni();
	Sprite * GetSprite() const;
	const Size & GetContentSize() const;
};

#endif // !__SPRITEANIMATOR_H__
