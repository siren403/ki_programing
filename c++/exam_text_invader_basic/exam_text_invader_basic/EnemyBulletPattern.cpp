#include "stdafx.h"
#include "EnemyBulletPattern.h"


CEnemyBulletPattern::CEnemyBulletPattern()
{
}


CEnemyBulletPattern::~CEnemyBulletPattern()
{
}

void CEnemyBulletPattern::Clean(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Clean(tpPixel);
	}
}

void CEnemyBulletPattern::Update()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Update();
	}
}

void CEnemyBulletPattern::Display(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Display(tpPixel);
	}
}

void CEnemyBulletPattern::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Destroy();
	}

	delete this;
}

void CEnemyBulletPattern::SetAlive(bool tIsAlive)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->SetAlive(tIsAlive);
	}
}

bool CEnemyBulletPattern::GetAlive()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		//속한 탄들 중 하나라도 살아있다면 
		if (mBullets[i]->GetAlive() == true)
		{
			//패턴 인스턴스가 살아있다고 판단
			return true;
		}
	}
	//모든 탄이 죽은 상태라면 현재 인스턴스도 죽은상태라고 판단
	return false;
}

void CEnemyBulletPattern::SetPositionForFire(int tX, int tY)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->SetPositionForFire(tX, tY);
	}
}

CEnemyBulletPattern & CEnemyBulletPattern::AddBullet(CEnemyBullet * tpEnemyBullet)
{
	mBullets.push_back(tpEnemyBullet);
	mBullets.back()->SetAlive(false);
	return *this;
}
