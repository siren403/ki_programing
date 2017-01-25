#ifndef __B2NODE_H__
#define __B2NODE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "b2WorldBoxData.h"
#include "b2CollisionData.h"

using namespace cocos2d;


class b2Node : public Node
{
private:
	//friend class b2LayerContactListener;
	unsigned int mb2Tag = 0;
	bool mIsWorldBoxCollision = false;

protected:
	b2Body * mpBody = nullptr;
	b2Body * CreateBodyByNodeSync(b2World * world,b2BodyDef * tBodyDef);
public:
	CREATE_FUNC(b2Node);
	virtual bool init() override;

	virtual void OnCollisionEnter(b2CollisionData * data);
	virtual void OnCollisionStay(b2CollisionData * data);
	virtual void OnCollisionExit(b2CollisionData * data);

	//b2Layer->AddChild->Call
	virtual void CreateBody(b2World * world);
	b2Body * GetBody();
	void Setb2Tag(int tag);
	int Getb2Tag();
	void SetDestroyTag();
	bool IsDestroyTag();
	bool IsWorldBoxCollision();
	void SetWorldBoxCollision(bool isCollision);
};


#endif // !__B2NODE_H__
