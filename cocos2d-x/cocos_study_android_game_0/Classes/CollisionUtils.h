#ifndef __COLLISIONUTILS_H__
#define __COLLISIONUTILS_H__

#include "cocos2d.h"
#include <vector>


using namespace cocos2d;
using namespace std;

class CollisionUtils
{
private:
	static CollisionUtils * mInstance;
	CollisionUtils();
	~CollisionUtils();
public:
	static CollisionUtils * GetInst();

private:
	vector<Vec2> mNormals;
public:
	bool ContainsPointToPixel(Sprite * sprite, Image * image, Vec2 pos);
	Vec2 GetPosToRectNormal(Node * node, Vec2 worldPos);
	float ConvertPositiveAtan2(float y,float x);
	void LogRect(Rect rect);
};

#endif // !__COLLISIONUTILS_H__
