#include "SpriteVector.h"

SpriteVector::SpriteVector()
{
}

SpriteVector::SpriteVector(int reserve)
{
	mSprites.reserve(reserve);
}

SpriteVector::~SpriteVector()
{
}

Vector<Sprite*>& SpriteVector::GetSprites()
{
	return mSprites;
}
