// exam_0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{

	//printf("Hello World\n");
	/*
	int tA = 0;
	int tB = 0;

	tA = 3;
	tB = 2;

	float tResult = 0;

	tResult = tA + tB;
	printf("%f\n", tResult);


	tResult = tA - tB;
	printf("%f\n", tResult);


	tResult = tA * tB;
	printf("%f\n", tResult);


	tResult = (float)tA / tB;
	printf("%f\n", tResult);
	*/

	/*
	int ti = 0;
	int tj = 0;
	int tResult = 0;

	for (ti = 1; ti <= 9; ti++)
	{
		for (tj = 1; tj <= 9; tj++) 
		{
			tResult = ti * tj;

			printf("%d * %d", ti, tj);
			printf("= %d", tResult);
			printf("\n");
		
		}
	}
	*/


	int tInput = 0;

	while (1)
	{
	
		scanf_s("%d", &tInput);

		if (9 == tInput)
		{
			break;
		}
	}

	printf("==================\n");

	//int tInput = 0;
	//scanf_s("%d", &tInput);

    return 0;
}








