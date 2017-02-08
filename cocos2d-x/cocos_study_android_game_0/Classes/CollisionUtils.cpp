#include "CollisionUtils.h"

#define PI 3.14159

CollisionUtils * CollisionUtils::mInstance = nullptr;


CollisionUtils::CollisionUtils()
{
	mNormals.reserve(8);//vert 4,radian 4
}

CollisionUtils::~CollisionUtils()
{

}

CollisionUtils * CollisionUtils::GetInst()
{
	if (mInstance == nullptr)
	{
		mInstance = new CollisionUtils();
	}
	return mInstance;
}

bool CollisionUtils::ContainsPointToPixel(Sprite * sprite, Image * image, Vec2 pos)
{
	bool result = false;

	Vec2 nodePos = sprite->convertToNodeSpace(pos);
	nodePos.x = (int)nodePos.x;//소수점을 정리하지 않으면 정확한 값을 기대할 수 없다
	nodePos.y = (int)nodePos.y;//

	if (nodePos.x < 0 || nodePos.x>sprite->getContentSize().width ||
		nodePos.y < 0 || nodePos.y>sprite->getContentSize().height)
	{
		return result;
	}

	unsigned char * pData = image->getData();

	unsigned char* pPixel = pData + (int)((nodePos.x + (sprite->getContentSize().height - nodePos.y) * sprite->getContentSize().width) * 4);
	//unsigned char r = *pPixel;
	//unsigned char g = *(pPixel + 1);
	//unsigned char b = *(pPixel + 2);
	//unsigned char a = *(pPixel + 3);
	//log("RGBA : %i, %i, %i, %i", r, g, b, a);

	if (0 != *(pPixel + 3))
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

Vec2 CollisionUtils::GetPosToRectNormal(Node * node, Vec2 worldPos)
{
	mNormals.clear();
	Vec2 result;

	auto rect = utils::getCascadeBoundingBox(node);//world

	mNormals.push_back(Vec2(rect.getMaxX(), rect.getMaxY()));
	mNormals.push_back(Vec2(rect.getMinX(), rect.getMaxY()));
	mNormals.push_back(Vec2(rect.getMinX(), rect.getMinY()));
	mNormals.push_back(Vec2(rect.getMaxX(), rect.getMinY()));

	auto center = node->getPosition();
	center.x = rect.getMinX() + ((rect.getMaxX() - rect.getMinX()) * 0.5);
	center.y = rect.getMinY() + ((rect.getMaxY() - rect.getMinY()) * 0.5);

	//log("center %f,%f", center.x, center.y);
	//LogRect(rect);

	Vec2 dir = worldPos - center;
	float radian = ConvertPositiveAtan2(dir.y, dir.x);
	//log("%f", CC_RADIANS_TO_DEGREES(radian));

	Vec2 vertDir;
	Vec2 rad;
	
	int vertCount = mNormals.size();
	for (int i = 0; i < mNormals.size(); i++)
	{
		int nextIndex = i == vertCount - 1 ? 0 : i + 1;
		vertDir = mNormals.at(i) - center;
		rad.x = ConvertPositiveAtan2(vertDir.y, vertDir.x);
		vertDir = mNormals.at(nextIndex) - center;
		rad.y = ConvertPositiveAtan2(vertDir.y, vertDir.x);
		//log("[%d,%d] %f to %f = %d,%d", i, nextIndex, CC_RADIANS_TO_DEGREES(rad.x), CC_RADIANS_TO_DEGREES(rad.y), 0, 1);

		if ((radian >= rad.x && radian <= rad.y)|| (rad.x > rad.y && (radian >= rad.x || radian <= rad.x)))
		{
			switch (i)
			{
			case 0:
				result = Vec2(0, 1);
				break;
			case 1:
				result = Vec2(-1, 0);
				break;
			case 2:
				result = Vec2(0, -1);
				break;
			case 3:
				result = Vec2(1, 0);
				break;
			}

			break;
		}
	}
	//log("%f,%f", result.x, result.y);
	
	return result;
}

float CollisionUtils::ConvertPositiveAtan2(float y, float x)
{
	float radian = atan2(y, x);
	if (radian < 0)
	{
		radian = (PI + radian) + PI;
	}
	return radian;
}

void CollisionUtils::LogRect(Rect rect)
{
	Vec2 topright = Vec2(rect.getMaxX(), rect.getMaxY());
	log("topright %f,%f", topright.x, topright.y);

	Vec2 topleft = Vec2(rect.getMinX(), rect.getMaxY());
	log("topleft %f,%f", topleft.x, topleft.y);

	Vec2 botleft = Vec2(rect.getMinX(), rect.getMinY());
	log("botleft %f,%f", botleft.x, botleft.y);

	Vec2 botright = Vec2(rect.getMaxX(), rect.getMinY());
	log("botright %f,%f", botright.x, botright.y);
}
