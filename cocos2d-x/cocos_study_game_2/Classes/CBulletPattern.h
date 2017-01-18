#ifndef __CBULLETPATTERN_H__
#define __CBULLETPATTERN_H__

#include "cocos2d.h"
#include "CBullet.h"

using namespace cocos2d;

class CBulletPattern : public CBullet
{
private:
	Vector<CBullet *> mBullets;
public:
	CREATE_FUNC(CBulletPattern);

	void pushBullet(CBullet * tBullet);
	void bulletReserve(int size);

	virtual bool getIsAlive() override;
	virtual void setIsAlive(bool tIsAlive) override;
	virtual void Shot(Vec2 tPos) override;

};

#endif // !__CBULLETPATTERN_H__
