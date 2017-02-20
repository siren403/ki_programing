#ifndef __FAKERPARTS_H__
#define __FAKERPARTS_H__

#include "EnemyParts.h"

class StopWatch;

class FakerSheep : public EnemyParts
{
private:
	Sprite * mFaceSprite = nullptr;
	StopWatch * mStopWatch = nullptr;
	int mFaceIndex = 0;
public:
	CREATE_FUNC(FakerSheep);
	virtual bool init() override;
	virtual void update(float dt) override;


};


#endif // !__FAKERPARTS_H__
