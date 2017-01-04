// exam_singleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DisplayManager.h"
#include <iostream>

using namespace std;

int main()
{
	CDisplayManager::GetInstance()->Display();
	CDisplayManager::GetInstance()->Display();
	CDisplayManager::GetInstance()->Display();
	CDisplayManager::GetInstance()->Display();

	CDisplayManager::GetInstance()->Destroy();
	int tInput = 0;
	cin >> tInput;


    return 0;
}

