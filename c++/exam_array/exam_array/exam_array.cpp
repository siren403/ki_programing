// exam_array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	/*int *tpBulletArray[5] = { NULL,NULL ,NULL ,NULL ,NULL };

	int ti = 0;
	int tCount = 5;

	for (ti = 0; ti < tCount; ti++)
	{
		tpBulletArray[ti] = new int();
		*tpBulletArray[ti] = ti;
	}

	for (ti = 0; ti < tCount; ti++)
	{
		cout << tpBulletArray[ti] << endl;
	}

	for (ti = 0; ti < tCount; ti++)
	{
		if (NULL != tpBulletArray[ti])
		{
			delete tpBulletArray[ti];
			tpBulletArray[ti] = NULL;
		}
	}*/

	int *tpBullets = NULL;

	tpBullets = new int[5];

	int ti = 0;
	int tCount = 5;

	for (ti = 0; ti < tCount; ti++)
	{
		tpBullets[ti] = ti;
	}
	for (ti = 0; ti < tCount; ti++)
	{
		cout << tpBullets[ti] << endl;
	}

	if (tpBullets != NULL)
	{
		delete[] tpBullets;
		tpBullets = NULL;

	}



    return 0;
}

