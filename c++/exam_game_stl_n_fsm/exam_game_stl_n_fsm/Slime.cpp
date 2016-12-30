#include "stdafx.h"
#include "Slime.h"
#include "Dice.h"

#include <iostream>
using namespace std;

CSlime::CSlime()
{
}


CSlime::~CSlime()
{
}

char CSlime::DoBattle(CPlayer * tPlayer)
{
	int tInput = 0;
	char tResult = 0;

	CDice tDice;

	while (1)
	{
		printf("\t");
		printf("[용사]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[슬라임]");
		DisplayGauge(mCurrentHealth, mHealth);
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

			tPlayer->DoAttack(this);
			if (this->GetCurrentHealth() == 0)
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
			printf("슬라임이 %d만큼 피해를 입혔다.", this->GetPower());
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
