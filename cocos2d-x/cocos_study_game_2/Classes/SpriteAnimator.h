#ifndef __SPRITEANIMATOR_H__
#define __SPRITEANIMATOR_H__

#include "cocos2d.h"

USING_NS_CC;


class SpriteAnimator : public Node
{
private:
	Sprite * mpSprite = nullptr;
	std::string mAniFileName = "";

	int mStartFrame = 0;
	int mEndFrame = 0;
	float mDelayTime = 0.0f;

	Action * mpRepeat = nullptr;
	
	void createAnimation();
public:
	static SpriteAnimator * create(
		const std::string& tAniFileName,
		int tStartFrame,
		int tEndFrame,
		float tDelayTime
	);

	CREATE_FUNC(SpriteAnimator);
	
	void runAni();
	void stopAni();
	const Sprite * getSprite() const;
	const Size & getContentSize() const;
};

#endif // !__SPRITEANIMATOR_H__
