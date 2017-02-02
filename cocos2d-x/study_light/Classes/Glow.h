#ifndef __GLOW_H__
#define __GLOW_H__

#include "cocos2d.h"

using namespace cocos2d;

class Glow : public Node
{
private:
	Sprite * mSprite = nullptr;
	float m_ctime = 0;
	void callbackColor(GLProgram* glProgram, Uniform* uniform);

public:
	CREATE_FUNC(Glow);
	virtual bool init() override;
	Sprite * GetSprite();
};

#endif // !__GLOW_H__
