#ifndef __B2ROPETARGET_H__
#define __B2ROPETARGET_H__

#include "b2Custom\b2Node.h"

class b2RopeTarget : public b2Node
{
private:
	b2RopeJoint * mpRope = nullptr;
	b2Body * mpRopeHead = nullptr;
public:
	CREATE_FUNC(b2RopeTarget);

	virtual bool init() override;

	virtual void CreateBody(b2World * world) override;
	virtual void OnCollisionEnter(b2CollisionData * data) override;
	virtual void OnCollisionStay(b2CollisionData * data) override;
	virtual void OnCollisionExit(b2CollisionData * data) override;

	void AttachTarget(b2Node * tTargetNode);
};

#endif // !__B2ROPETARGET_H__
