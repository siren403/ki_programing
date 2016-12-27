#include "stdafx.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

#define YES 'y'
#define NO 'n'

//State Values
#define TITLE 0
#define INIT 1
#define PLAY 2
#define QUIT 3

//Player,Monsters Kind
#define KIND_PLAYER 11
#define KIND_NORMAL_SLIME 12
#define KIND_BOSS_SLIME 13

#define MAP_LENGTH 5
#define MAX_HEALTH 10

using namespace std;

class CPlayer
{
private:
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;
	int mPosition = 0;

public:
	CPlayer();
	~CPlayer();
	//getter
	int GetHealth();
	int& GetCurrentHealth();
	int& GetPower();
	int GetPosition();
	//setter
	void SetHealth(int tHealth);
	void SetCurrentHealth(int tCurHealth);
	void SetPower(int tPower);
	void SetPosition(int tPosition);
	
	void DoMove(int tMap[], int tIndex);

};

class CSlime
{
private:
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;
public:
	//char(*mDoBattle)(CPlayer *tPlayer, CSlime *tSlime) = NULL;

	//getter
	int GetHealth();
	int& GetCurrentHealth();
	int& GetPower();
	//setter
	void SetHealth(int tHealth);
	void SetCurrentHealth(int tCurHealth);
	void SetPower(int tPower);
};

class CMap
{
private:
	int mMap[MAP_LENGTH] = { 0 };//지정한 맵길이로 요소들 초기화

public:
	void DrawMap();
	int* GetMap();
	char CheckSlimeEncount(CPlayer *tPlayer);
};

class CDice
{
private:
	int mDiceNumber = 0;
public:
	int DoThrow(int tMaxNumber);
	int GetDiceNumber();
};

class CNormalBattle
{
private:
	int tInput = 0;
	char tResult = 0;

	CDice tDice;
public:
	char DoBattle(CPlayer *tPlayer, CSlime *tSlime);
	void DoAttack(int &tPower, int &tTargetHealth);
};

class CBossBattle
{
private:
	int tPlayerCard = 0;
	int tCompareResult = 0;

	char tResult = 0;
	CDice tSlimeDice;
public:
	char DoBattle(CPlayer *tPlayer, CSlime *tSlime);
	char CheckCompareCard(int tPlayerCard, int tSlimeCard);
	void DisplayCard(int tCardValue);
	void DoAttack(int &tPower, int &tTargetHealth);
};

class CGameManager
{
private:
	int mGameState = 0;//게임시작 시 타이틀 상태
	int mInput = 0;//Input입력 받는 변수
	char mIsContinue = 0;

	CMap mMap;
	CPlayer *mPlayer = NULL;
	CSlime *mNormalSlime = NULL;
	CSlime *mBossSlime = NULL;

	CNormalBattle mNormalBattle;
	CBossBattle mBossBattle;
public:
	CGameManager();
	~CGameManager();

	CPlayer& GetPlayer();
	CSlime& GetSlime(int tKind);

	int DisplayTitle();
	void Play();
	char GetIsContinue();
};


void DisplayGauge(int tCurrentValue, int tMaxValue);


int main()
{

	srand(time(NULL));//랜덤 시드 지정

	CGameManager tGameManager;

	tGameManager.Play();

	return 0;
}

//타이틀 화면을 그리고 
//시작,종료를 입력받는다.
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

//플레이어의 위치정보를 변경하고
//맵의 위치 정보를 갱신한다.
//void PlayerToMove(Player *tPlayer, int tMap[], int tIndex)
//{
//	if (tIndex >= 0 && tIndex < MAP_LENGTH)
//	{
//		tMap[tPlayer->GetPosition()] = 0;
//		tMap[tIndex] = KIND_PLAYER;
//		tPlayer->SetPosition(tIndex);
//	}
//	else
//	{
//		int tInput = 0;
//
//		printf("\t");
//		printf("[ 이동 할 수 없다... ]");
//		printf("\n");
//		printf("Input Any Key");
//		printf("\n");
//		cin >> tInput;
//	}
//
//}

//현재의 맵 상태를 그린다.
void CMap::DrawMap()
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n");
	printf("==");
	for (ti = 0; ti < MAP_LENGTH; ti++)
	{
		switch (mMap[ti])
		{
		case KIND_PLAYER:
			printf("[  PLAYER  ]==");
			break;
		case KIND_NORMAL_SLIME:
			printf("[  SLIME   ]==");
			break;
		case KIND_BOSS_SLIME:
			printf("[BOSS SLIME]==");
			break;
		case 0://없음
		default:
			printf("[          ]==");
			break;
		}
	}
	printf("\n");
	printf("====================================");
	printf("====================================");
	printf("\n\n");

}

int * CMap::GetMap()
{
	return mMap;
}

//플레이어가 적을 마주보고 있는지 검사한다.
char CMap::CheckSlimeEncount(CPlayer *tPlayer)
{
	char tResult = 0;

	if (tPlayer != NULL && tPlayer->GetPosition() < MAP_LENGTH - 1)
	{
		if (mMap[tPlayer->GetPosition() + 1] != 0)
		{
			tResult = 1;
		}
	}
	return tResult;
}


//주사위를 던져 눈금을 리턴한다.
int CDice::DoThrow(int tMaxNumber)
{
	mDiceNumber = rand() % tMaxNumber + 1;

	return mDiceNumber;
}

int CDice::GetDiceNumber()
{
	return mDiceNumber;
}

//플레이어와 슬라임의 패를 비교하여 결과를 리턴한다.
char CBossBattle::CheckCompareCard(int tPlayerCard, int tSlimeCard)
{
	char tResult = 0;

	switch (tPlayerCard)
	{
	case 1://가위
		switch (tSlimeCard)
		{
		case 1:
			tResult = 0;
			break;
		case 2:
			tResult = 2;
			break;
		case 3:
			tResult = 1;
			break;
		}
		break;
	case 2://바위
		switch (tSlimeCard)
		{
		case 1:
			tResult = 1;
			break;
		case 2:
			tResult = 0;
			break;
		case 3:
			tResult = 2;
			break;
		}
		break;
	case 3://보
		switch (tSlimeCard)
		{
		case 1:
			tResult = 2;
			break;
		case 2:
			tResult = 1;
			break;
		case 3:
			tResult = 0;
			break;
		}
		break;
	}

	return tResult;
}
//각 값에 맞는 텍스트를 출력한다.
void CBossBattle::DisplayCard(int tCardValue)
{
	switch (tCardValue)
	{
	case 1:
		printf("가위");
		break;
	case 2:
		printf("바위");
		break;
	case 3:
		printf("보");
		break;
	}
}

//현재값과 최대값을 입력받아 게이지는 출력한다.
void DisplayGauge(int tCurrentValue, int tMaxValue)
{
	int ti = 0;

	for (ti = 0; ti < tCurrentValue; ti++)
	{
		printf("■");
	}
	for (ti = 0; ti < tMaxValue - tCurrentValue; ti++)
	{
		printf("□");
	}

}



#pragma region Player 정의

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

int CPlayer::GetHealth()
{
	return mHealth;
}
void CPlayer::SetHealth(int tHealth)
{
	mHealth = tHealth;
}
int& CPlayer::GetCurrentHealth()
{
	return mCurrentHealth;
}
void CPlayer::SetCurrentHealth(int tCurHealth)
{
	mCurrentHealth = tCurHealth;
}
int& CPlayer::GetPower()
{
	return mPower;
}
void CPlayer::SetPower(int tPower)
{
	mPower = tPower;
}
int CPlayer::GetPosition()
{
	return mPosition;
}
void CPlayer::SetPosition(int tPosition)
{
	mPosition = tPosition;
}

void CPlayer::DoMove(int tMap[], int tIndex)
{
	if (tIndex >= 0 && tIndex < MAP_LENGTH)
	{
		tMap[mPosition] = 0;
		tMap[tIndex] = KIND_PLAYER;
		mPosition = tIndex;
	}
	else
	{
		int tInput = 0;

		printf("\t");
		printf("[ 이동 할 수 없다... ]");
		printf("\n");
		printf("Input Any Key");
		printf("\n");
		cin >> tInput;
	}
}
#pragma endregion

#pragma region Slime 정의

int CSlime::GetHealth()
{
	return mHealth;
}
int& CSlime::GetCurrentHealth()
{
	return mCurrentHealth;
}
int& CSlime::GetPower()
{
	return mPower;
}
void CSlime::SetHealth(int tHealth)
{
	mHealth = tHealth;
}
void CSlime::SetCurrentHealth(int tCurHealth)
{
	mCurrentHealth = tCurHealth;
}
void CSlime::SetPower(int tPower)
{
	mPower = tPower;
}



#pragma endregion

CGameManager::CGameManager()
{
	mGameState = TITLE;//게임시작 시 타이틀 상태
	mInput = 0;//Input입력 받는 변수
	mIsContinue = YES;

	mPlayer = new CPlayer();
	mNormalSlime = new CSlime();
	mBossSlime = new CSlime();

	//mNormalSlime->mDoBattle = mNormalBattle.DoBattle;//주사위 게임
	//mBossSlime->mDoBattle = mBossBattle.DoBattle;//가위,바위,보

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

CSlime & CGameManager::GetSlime(int tKind)
{
	if (tKind == KIND_NORMAL_SLIME)
		return *mNormalSlime;
	else
		return *mBossSlime;
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
				CSlime *tSlime = NULL;

				//현재 플레이어 위치+1의 마주보는 슬라임 종류
				tSlimeKind = mMap.GetMap()[mPlayer->GetPosition() + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t");
					printf("[ 일반 슬라임이 나타났다. ]");
					printf("\n\n");
					tSlime = mNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ 보스 슬라임이 나타났다. ]");
					printf("\n\n");
					tSlime = mBossSlime;
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

					if (tSlimeKind == KIND_NORMAL_SLIME)
					{
						tBattleResult = mNormalBattle.DoBattle(mPlayer, tSlime);
					}
					else if (tSlimeKind == KIND_BOSS_SLIME)
					{
						tBattleResult = mBossBattle.DoBattle(mPlayer, tSlime);
					}

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

char CGameManager::GetIsContinue()
{
	return mIsContinue;
}

char CNormalBattle::DoBattle(CPlayer * tPlayer, CSlime * tSlime)
{
	while (1)
	{
		printf("\t");
		printf("[용사]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[슬라임]");
		DisplayGauge(tSlime->GetCurrentHealth(), tSlime->GetHealth());
		printf("\n\n");

		printf("1. 주사위를 던진다.");
		printf("\n");
		cin >> tInput;

		printf("================================================");
		printf("\n\n");

		tDice.DoThrow(6);

		printf("\n\t   ");
		printf("주사위 . ");
		DisplayGauge(tDice.GetDiceNumber(), 6);
		printf("\n\n");

		if (4 <= tDice.GetDiceNumber())//4이상 승리
		{
			printf("\t");
			printf("공격!!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.", tPlayer->GetPower());
			printf("\n\n");

			DoAttack(tPlayer->GetPower(), tSlime->GetCurrentHealth());
			if (tSlime->GetCurrentHealth() == 0)
			{
				printf("\n\t\t");
				printf("[ 슬라임을 잡았다!! ]");
				printf("\n\n");

				if (tDice.DoThrow(3) <= 3)
				{
					printf("\t\t");
					printf("[ 용사가 강해졌다. ]");
					printf("\n\n");
					tPlayer->SetHealth(tPlayer->GetHealth() + 2);
					tPlayer->SetPower(tPlayer->GetPower() + 2);
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDice.GetDiceNumber())//3이하 패배
		{
			printf("\t");
			printf("슬라임이 %d만큼 피해를 입혔다.", tSlime->GetPower());
			printf("\n\n");

			DoAttack(tSlime->GetPower(), tPlayer->GetCurrentHealth());
			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;
}


void CNormalBattle::DoAttack(int &tPower, int &tTargetHealth)
{
	tTargetHealth -= tPower;
	if (tTargetHealth < 0)
	{
		tTargetHealth = 0;
	}
}


char CBossBattle::DoBattle(CPlayer * tPlayer, CSlime * tSlime)
{
	printf("\n\t\t");
	printf("[ 가위,바위,보 게임 ]");
	printf("\n\n\t");
	printf("가위,바위,보를 내서 이긴쪽이 공격한다!");
	printf("\n\n\n");

	while (1)
	{
		printf("[용사]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[보스 슬라임]");
		DisplayGauge(tSlime->GetCurrentHealth(), tSlime->GetHealth());
		printf("\n\n");

		printf("[1]:가위, [2]:바위, [3]:보");
		printf("\n\n");
		printf("선택하세요 : ");
		cin >> tPlayerCard;
		printf("\n");
		printf("================================================");
		printf("\n");


		tSlimeDice.DoThrow(3);

		tCompareResult = CheckCompareCard(tPlayerCard, tSlimeDice.GetDiceNumber());

		printf("\n\t\t");
		printf("[용사]");
		DisplayCard(tPlayerCard);
		printf(" vs ");
		DisplayCard(tSlimeDice.GetDiceNumber());
		printf("[슬라임]");
		printf("\n\n");


		if (0 == tCompareResult)//무승부
		{
			printf("\t\t\t");
			printf("비겼습니다.");
			printf("\n\n");

		}
		else if (1 == tCompareResult)//승리
		{
			printf("\t");
			printf("승리!!");
			printf("용사가 적에게 %d만큼 피해를 입혔다.", tPlayer->GetPower());
			printf("\n\n");

			DoAttack(tPlayer->GetPower(), tSlime->GetCurrentHealth());
			if (tSlime->GetCurrentHealth() == 0)
			{
				printf("\n\t\t");
				printf("[ 슬라임을 잡았다!! ]");
				printf("\n\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//패배
		{
			printf("\t");
			printf("패배...");
			printf("보스 슬라임이 %d만큼 피해를 입혔다.", tSlime->GetPower());
			printf("\n\n");

			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

void CBossBattle::DoAttack(int &tPower, int &tTargetHealth)
{
	tTargetHealth -= tPower;
	if (tTargetHealth < 0)
	{
		tTargetHealth = 0;
	}
}