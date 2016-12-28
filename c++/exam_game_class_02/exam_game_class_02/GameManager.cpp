#include "stdafx.h"
#include "GameManager.h"

#include <iostream>

using namespace std;

CGameManager::CGameManager()
{
	mGameState = TITLE;//게임시작 시 타이틀 상태
	mInput = 0;//Input입력 받는 변수
	mIsContinue = YES;

	mPlayer = new CPlayer();
	mNormalSlime = new CSlime();
	mBossSlime = new CBossSlie();

}


CGameManager::~CGameManager()
{
	//각 동적할당 변수들 초기화
	if (mPlayer != NULL)
	{
		delete mPlayer;
		mPlayer = NULL;
	}
	if (mNormalSlime != NULL)
	{
		delete mNormalSlime;
		mNormalSlime = NULL;
	}
	if (mBossSlime != NULL)
	{
		delete mBossSlime;
		mBossSlime = NULL;
	}
}


CPlayer & CGameManager::GetPlayer()
{
	return *mPlayer;
}

CMonster & CGameManager::GetMonster(int tKind)
{
	if (tKind == KIND_NORMAL_SLIME)
		return *mNormalSlime;
	else
		return *mBossSlime;
}

int CGameManager::DisplayTitle()
{
	int tInput = 0;

	printf("\n\n\t");
	printf("[ 용사는 일차원 ]");
	printf("\n\n\n");

	printf("1.게임 시작");
	printf("\n");
	printf("2.종료");
	printf("\n");

	cin >> tInput;

	if (tInput == 1)//시작 선택 시 상태를 초기화로 변경
	{
		tInput = INIT;
	}
	else//종료
	{
		tInput = QUIT;
	}

	return tInput;
}

void CGameManager::Play()
{
	while (NO != mIsContinue)
	{
		switch (mGameState)
		{
		case TITLE://타이틀
			mGameState = DisplayTitle();
			break;
		case INIT://재시작 시 초기화 값
			mPlayer->SetHealth(5);
			mPlayer->SetCurrentHealth(mPlayer->GetHealth());
			mPlayer->SetPower(1);

			mNormalSlime->SetHealth(5);
			mNormalSlime->SetCurrentHealth(mNormalSlime->GetHealth());
			mNormalSlime->SetPower(1);

			mBossSlime->SetHealth(10);
			mBossSlime->SetCurrentHealth(mBossSlime->GetHealth());
			mBossSlime->SetPower(2);


			//플레이어 초기위치로 이동
			mPlayer->DoMove(mMap.GetMap(), 0);
			//2번에는 일반 슬라임이 있다. 
			mMap.GetMap()[2] = KIND_NORMAL_SLIME;
			//4번에는 보스 슬라임이 있다.
			mMap.GetMap()[4] = KIND_BOSS_SLIME;


			mGameState = PLAY;
			break;
		case PLAY:
			mMap.DrawMap();

			if (mMap.CheckSlimeEncount(mPlayer))//적과 마주침
			{
				int tSlimeKind = 0;
				CMonster *tMonster = NULL;

				//현재 플레이어 위치+1의 마주보는 슬라임 종류
				tSlimeKind = mMap.GetMap()[mPlayer->GetPosition() + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t");
					printf("[ 일반 슬라임이 나타났다. ]");
					printf("\n\n");
					tMonster = mNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ 보스 슬라임이 나타났다. ]");
					printf("\n\n");
					tMonster = mBossSlime;
				}

				printf("1.싸움을 건다!!");
				printf("\n");
				printf("2.도망친다..");
				printf("\n");
				cin >> mInput;

				if (mInput == 1)
				{
					int tBattleResult = 0;
					//printf("\t[ 전투가 시작했다!! ]\n\n");

					tBattleResult = tMonster->DoBattle(/*this, */mPlayer);

					if (tBattleResult == 1)//승리
					{
						//용사 체력 회복
						mPlayer->SetCurrentHealth(mPlayer->GetHealth());

						//슬라임이 있던 위치 초기화
						mMap.GetMap()[mPlayer->GetPosition() + 1] = 0;
						//다음 위치로 이동
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() + 1);
					}
					else if (tBattleResult == 0)//패배
					{
						printf("\n\n\t\t");
						printf("[ 용사는 죽었다... ]");
						printf("\n\n\n");

						mGameState = QUIT;
					}

					printf("Input Any Key");
					printf("\n");
					cin >> mInput;
				}
				else if (mInput == 2)
				{
					printf("\t");
					printf("[ 용사는 도망쳤다... ]");
					printf("\n");

					mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() - 1);

				}
			}
			else//적과 마주치지 않음
			{
				if (mPlayer->GetPosition() != MAP_LENGTH - 1)//맵 끝에 도달하지 않았으면
				{
					printf("\t");
					printf("[ 어떻게 할까? ]");
					printf("\n\n");
					printf("1.전진하기");
					printf("\n");
					printf("2.돌아가기");
					printf("\n");


					cin >> mInput;

					if (mInput == 1)
					{
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() + 1);

					}
					else if (mInput == 2)
					{
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() - 1);
					}
				}
				else
				{
					printf("\t");
					printf("[ 게임을 클리어하였습니다. ]");
					printf("\n\n");
					printf("Input Any Key");
					printf("\n");

					cin >> mInput;
					mGameState = QUIT;
				}
			}

			break;
		case QUIT://종료
			printf("\n\n\n");
			printf("계속하시겠습니까?(y/n): ");
			cin >> mIsContinue;
			if (YES == mIsContinue)
			{
				mGameState = 0;
			}
			break;
		}
		system("cls");
	}
}

