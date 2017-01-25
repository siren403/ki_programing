#ifndef __B2COLLISIONDATA_H__
#define __B2COLLISIONDATA_H__

#include "b2WorldBoxData.h"

class b2Fixture;
class b2Node;

class b2CollisionData
{
public:
	b2Fixture * other = nullptr;
	b2Node * otherNode = nullptr;
	WorldBoxTag worldBoxTag = WorldBoxTag::TAG_NONE;
};


#endif // !__B2COLLISIONDATA_H__

