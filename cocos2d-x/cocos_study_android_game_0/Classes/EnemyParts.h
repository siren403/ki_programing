#ifndef __ENEMYPARTS_H__
#define __ENEMYPARTS_H__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class Enemy;

class EnemyParts : public Actor
{
private:
	Sprite * mSprite = nullptr;
	int mHP = 0;
	float mHitDelay = 0;
	float mCurrentHitDelay = 0;
protected:
	//get,set
	Sprite * SetSprite(Sprite * sprite,int localZOrder = 0);
public:
	CREATE_FUNC(EnemyParts);
	virtual bool init() override;
	virtual void update(float dt) override;

	//setter, getter
	virtual void SetAlive(bool tIsAlive) override;
	virtual const Size GetPartsSize();
	void SetHP(int tHP);
	Sprite * GetSprite();


	void Hit();
};


#endif // !__CENEMYPARTS_H__
