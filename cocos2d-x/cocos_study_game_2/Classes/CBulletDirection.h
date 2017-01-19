#ifndef __CBULLETDIRECTION_H__
#define __CBULLETDIRECTION_H__

#include "cocos2d.h"
#include "CBullet.h"

using namespace cocos2d;

class CBulletDirection : public CBullet
{
protected:
	virtual void bulletUpdate(float dt) override;
public:
	CREATE_FUNC(CBulletDirection);
	virtual bool init() override;
};

#endif // !__CBULLETDIRECTION_H__
