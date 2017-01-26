#ifndef __B2BLOCK_H__
#define __B2BLOCK_H__

#include "b2Custom\b2Node.h"

class b2Block : public b2Node
{
private:
	Sprite * mSprite = nullptr;
public:
	CREATE_FUNC(b2Block);
	virtual bool init() override;

	virtual void CreateBody(b2World * world) override;
	virtual void OnCollisionEnter(b2CollisionData * data) override;
	virtual void OnCollisionStay(b2CollisionData * data) override;
	virtual void OnCollisionExit(b2CollisionData * data) override;
};

#endif // !__B2BLOCK_H__
