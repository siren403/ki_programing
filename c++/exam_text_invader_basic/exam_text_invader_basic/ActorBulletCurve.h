#pragma once
#include "ActorBullet.h"

class CActorBulletCurve :
	public CActorBullet
{
private:
	unsigned int ShotTime = 0;
	int mRadius = 0;
public:
	CActorBulletCurve();
	~CActorBulletCurve();

	virtual void Update() override;
	virtual void SetPositionForFire(int tX, int tY) override;

	void SetRadius(int tRadius);
};

