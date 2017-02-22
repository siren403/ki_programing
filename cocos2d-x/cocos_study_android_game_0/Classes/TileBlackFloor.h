#ifndef __TILEBLACKFLOOR_H__
#define __TILEBLACKFLOOR_H__

#include "MapTile.h"

class StopWatch;

class TileBlackFloor : public MapTile
{
public:
	CREATE_FUNC(TileBlackFloor);
	virtual bool init() override;
	virtual void update(float dt) override;
	
	virtual void SetHighlight(bool isHighlight) override;
private:
	StopWatch * mStopWatch = nullptr;
	GLProgramState * mGLState = nullptr;
	bool mIsHighlight = false;
	bool mIsEndHighlight = false;

};


#endif