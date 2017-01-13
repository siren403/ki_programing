#include "Dice.h"
#include <stdlib.h>
#include <time.h>



bool Dice::init()
{
	if (!Node::init())
	{
		return false;
	}
	srand(time(nullptr));

	mpDiceSprite = Sprite::create("dice.png");
	this->addChild(mpDiceSprite);
	SetNumberByTextureRect(0);

	return true;
}

int Dice::throwDice()
{
	int tNumber = rand() % 6;
	SetNumberByTextureRect(tNumber);
	return tNumber + 1;
}

void Dice::SetNumberByTextureRect(int n)
{
	float tWidth = (mpDiceSprite->getTexture()->getPixelsWide() + 1.3f) / 6;
	int tHeight = mpDiceSprite->getTexture()->getPixelsHigh();
	mpDiceSprite->setTextureRect(Rect(n*tWidth, 0, tWidth, tHeight));
}
