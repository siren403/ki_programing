#include "CollisionUtils.h"

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
