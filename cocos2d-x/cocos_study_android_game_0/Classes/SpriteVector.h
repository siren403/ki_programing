#ifndef __SPRITEVECTOR_H__
#define __SPRITEVECTOR_H__

#include "cocos2d.h"

using namespace cocos2d;

class SpriteVector : public Ref
{
private:
	Vector<Sprite *> mSprites;
public:
	SpriteVector();
	SpriteVector(int reserve);
	~SpriteVector();

	Vector<Sprite *> & GetSprites();
};

#endif // !__SPRITEVECTOR_H__
