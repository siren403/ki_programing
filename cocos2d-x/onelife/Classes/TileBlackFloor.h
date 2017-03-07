#ifndef __TILEBLACKFLOOR_H__
#define __TILEBLACKFLOOR_H__

#include "MapTile.h"

class StopWatch;
class SWPointColor;


class TileBlackFloor : public MapTile
{
public:
	CREATE_FUNC(TileBlackFloor);
	virtual ~TileBlackFloor();
	virtual bool init() override;
	virtual void update(float dt) override;
	
	virtual void SetHighlight(bool isHighlight) override;
	virtual void SetHighlight(bool isHighlight,float delay) override;

private:
	StopWatch * mDurationWatch = nullptr;
	StopWatch * mDelayWatch = nullptr;
	SWPointColor * mPointColor = nullptr;
	
	float mDuration = 0;
	float mDelay = 0;
	bool mIsHighlight = false;

};


#endif