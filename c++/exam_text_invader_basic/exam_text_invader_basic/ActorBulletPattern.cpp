#include "stdafx.h"
#include "ActorBulletPattern.h"
#include "Enemy.h"

#include <iostream>

using namespace std;

CActorBulletPattern::CActorBulletPattern()
{

}


CActorBulletPattern::~CActorBulletPattern()
{

}

void CActorBulletPattern::Clean(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Clean(tpPixel);
	}
}

void CActorBulletPattern::Update()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive() == true)
		{
			mBullets[ti]->Update();
		}
	}
}

void CActorBulletPattern::Display(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive() == true)
		{
			mBullets[ti]->Display(tpPixel);
		}
	}
}

void CActorBulletPattern::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Destroy();
	}

	delete this;
}

void CActorBulletPattern::SetAlive(bool tIsAlive)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->SetAlive(tIsAlive);
	}
}

bool CActorBulletPattern::GetAlive()
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

void CActorBulletPattern::SetPositionForFire(int tX, int tY)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->SetPositionForFire(tX, tY);
	}
}

bool CActorBulletPattern::DoCollisionWithEnemy(CEnemy * tpEnemy)
{

	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive())
		{
			if (mBullets[ti]->GetX() == tpEnemy->GetX()
				&& mBullets[ti]->GetY() == tpEnemy->GetY())
			{
				cout << "ActorBullet VS Enemy Collision" << endl;
				tResult = true;
			}
		}
	}

	return tResult;
}

CActorBulletPattern & CActorBulletPattern::AddBullet(CActorBullet * tpEnemyBullet)
{
	mBullets.push_back(tpEnemyBullet);
	mBullets.back()->SetAlive(false);
	return *this;
}
