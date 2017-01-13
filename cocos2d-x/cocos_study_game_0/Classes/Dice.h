#ifndef __DICE_H__
#define __DICE_H__

#include "cocos2d.h"

USING_NS_CC;

class Dice : public Node
{
private:
	Sprite * mpDiceSprite = nullptr;
	void SetNumberByTextureRect(int n);
public:
	virtual bool init() override;
	int throwDice();

	CREATE_FUNC(Dice);
};

#endif // !__DICE_H__
