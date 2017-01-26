#ifndef __B2BULLET_H__
#define __B2BULLET_H__

#include "b2Custom\b2Node.h"

class b2Bullet : public b2Node
{
private:
	Sprite * mpSprite = nullptr;
public:
	CREATE_FUNC(b2Bullet);
	virtual bool init() override;

	virtual void OnCollisionEnter(b2CollisionData * data) override;
	virtual void OnCollisionStay(b2CollisionData * data) override;
	virtual void OnCollisionExit(b2CollisionData * data) override;
	virtual void CreateBody(b2World * world) override;

};

#endif // !__BULLET_H__
