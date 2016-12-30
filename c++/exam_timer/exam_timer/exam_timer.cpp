// exam_timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <Windows.h>
#include <WinBase.h>

using namespace std;

#define DELAY_INTERVAL 1000

void OnTimeDoSomething();

int main()
{

	void(*tpPtr)() = NULL;
	tpPtr = OnTimeDoSomething;


	int tDelay = 0;
	int tTemp = 0;

	int tCount = 0;

	while (true)
	{
		if (0 == tDelay)
		{
			tDelay = GetTickCount();//시작시간
		}

		tTemp = GetTickCount();//현재시간

		if (tTemp - tDelay >= DELAY_INTERVAL)//현재 시간 - 시작시간 = 지나간 시간
		{
			tpPtr();
			cout << "Count:" << tCount << ", tTemp:" << tTemp << "Delay:" << tDelay << endl;
			tCount++;
			tDelay = tTemp;//시작시간 초기화
		}
	}

    return 0;
}

void OnTimeDoSomething()
{
	cout << "Timer Alive!" << endl;
}
