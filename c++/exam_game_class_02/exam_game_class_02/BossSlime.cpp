#include "stdafx.h"
#include "BossSlime.h"
#include "Dice.h"
#include <iostream>

using namespace std;

CBossSlie::CBossSlie()
{
}


CBossSlie::~CBossSlie()
{
}

char CBossSlie::DoBattle(CPlayer * tPlayer)
{
	int tPlayerCard = 0;
	int tCompareResult = 0;

	char tResult = 0;
	CDice tSlimeDice;

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
		DisplayGauge(mCurrentHealth, mHealth);
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

			tPlayer->DoAttack(this);
			if (mCurrentHealth == 0)
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
			printf("보스 슬라임이 %d만큼 피해를 입혔다.", mPower);
			printf("\n\n");

			DoAttack(tPlayer);
			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;

}

char CBossSlie::CheckCompareCard(int tPlayerCard, int tSlimeCard)
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

void CBossSlie::DisplayCard(int tCardValue)
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
