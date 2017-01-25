#ifndef __B2LAYERCONTACTLISTENER_H__
#define __B2LAYERCONTACTLISTENER_H__

#include "Box2D\Box2D.h"
#include "b2Node.h"

typedef void(*ContactCallback)(b2Node *, b2CollisionData * data);

class b2LayerContactListener : public b2ContactListener
{
private:
	void OnNodeCallback(b2Contact *contact,ContactCallback callback);
public:
	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // !__B2LAYERCONTACTLISTENER_H__
