// exam_struct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

#define ID_LEN		20
#define MAX_SPD		200
#define FUEL_STEP	2
#define ACC_STEP	10
#define BRK_STEP	10

class Car
{
private:
 	char gamerID[ID_LEN];
	int fuelGuage;
	int curSpeed;
public:
	void InitMembers(char *ID, int fuel);
	void ShowCarState() const;
	void Accel();
	void Break();
};


int main()
{
	cout << "Exam01 : " << endl;

	Car run99;
	run99.InitMembers("99",100);
	run99.Accel();
	run99.Accel();
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();



    return 0;
}

void Car::InitMembers(char *ID, int fuel)
{
	strcpy_s(gamerID, ID);
	fuelGuage = fuel;
	curSpeed = 0;
}


void Car::ShowCarState() const
{
	cout << "소유자ID: " << gamerID << endl;
	cout << "연료량: " << fuelGuage << "%" << endl;
	cout << "현재속도: " << curSpeed << "km/s" << endl << endl;
}

void Car::Accel()
{
	if (fuelGuage <= 0)
		return;
	else
		fuelGuage -= FUEL_STEP;

	if (curSpeed + ACC_STEP >= MAX_SPD)
	{
		curSpeed = MAX_SPD;
		return;
	}

	curSpeed += ACC_STEP;
}

void Car::Break()
{
	if (curSpeed < BRK_STEP)
	{
		curSpeed = 0;
		return;
	}
	curSpeed -= BRK_STEP;
}
