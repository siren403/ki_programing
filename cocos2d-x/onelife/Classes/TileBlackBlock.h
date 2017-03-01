#ifndef __TILEBLACKBLOCK_H__
#define __TILEBLACKBLOCK_H__

#include "MapTile.h"


class StopWatch;
class SWPointColor;

class TileBlackBlock : public MapTile
{
public:
	CREATE_FUNC(TileBlackBlock);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual ~TileBlackBlock();

	//virtual void SetHighlight(bool isHighlight) override;
	virtual void SetHighlight(bool isHighlight, float delay) override;
private:
	StopWatch * mStopWatch = nullptr;
	StopWatch * mDelayWatch = nullptr;
	SWPointColor * mShaderPointColor = nullptr;
	bool mIsHighlight = false;
	float mDuration = 0;
	float mDelay = 0;
};

#endif // !__TILEBLACKBLOCK_H__
