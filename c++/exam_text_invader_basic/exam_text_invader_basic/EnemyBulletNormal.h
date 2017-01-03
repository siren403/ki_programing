#pragma once
#include "EnemyBullet.h"

//현재 방향과 속도값으로 계속 움직이는 패턴
class CEnemyBulletNormal :
	public CEnemyBullet
{
public:
	CEnemyBulletNormal();
	CEnemyBulletNormal(int, int, int);
	~CEnemyBulletNormal();

	virtual void Update() override;
};

