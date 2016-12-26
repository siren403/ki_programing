// queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define MAX 10

using namespace std;

int Queue[MAX] = { 0 };
int Front = 0;
int Rear = 0;

void InitializeQueue();
void Put(int);
int Get();
void DisplayQueue();

int main()
{
	InitializeQueue();

	Put(1);
	Put(3);
	Put(10);
	Put(20);
	Put(7);

	DisplayQueue();

	cout << Get() << endl;
	cout << Get() << endl;
	cout << Get() << endl;

	DisplayQueue();

    return 0;
}


void InitializeQueue()
{
	Front = 0;
	Rear = 0;
}
void Put(int num)
{
	Queue[Rear] = num;
	Rear += 1;

	if (Rear >= MAX)
	{
		Rear = 0;
	}
}
int Get()
{
	int result = 0;

	result = Queue[Front];
	Front += 1;

	if (Front >= MAX)
	{
		Front = 0;
	}

	return result;
}
void DisplayQueue()
{
	int i = 0;
	cout << "Front -> " << ends;

	for (int i = Front; i < Rear; i++)
	{
		cout << Queue[i] << " -> " << ends;
	}
	cout << "end" << endl;
}

