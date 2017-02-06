#include "CollisionUtils.h"

bool CollisionUtils::ContainsPointToPixel(Sprite * sprite, Image * image, Vec2 pos)
{
	bool result = false;

	pos = sprite->convertToNodeSpace(pos);

	if (pos.x < 0 || pos.x>sprite->getContentSize().width ||
		pos.y < 0 || pos.y>sprite->getContentSize().height)
	{
		return result;
	}

	pos.y = sprite->getContentSize().height - pos.y;

	unsigned char * pData = image->getData();

	int tIndex = (pos.y * sprite->getContentSize().width + pos.x) * 4 + 3;
	unsigned char tAlpha = pData[tIndex];

	if (0 != tAlpha)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}
