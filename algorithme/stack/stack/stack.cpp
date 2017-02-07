// stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node
{
	int Data = 0;
	Node *Next = NULL;
};

void InitializeStack(void);
void Push(int num);
int Pop(void);
void DisplayStack(void);

Node *Head = NULL;
Node *End = NULL;

Node *ptrNode = NULL;

int main()
{
	int result = 0;
	InitializeStack();

	Push(1);
	Push(3);
	Push(10);
	Push(20);
	Push(12);

	DisplayStack();

	cout << "Pop : " << Pop() << endl;
	cout << "Pop : " << Pop() << endl;
	cout << "Pop : " << Pop() << endl;

	DisplayStack();

    return 0;
}

void InitializeStack(void)
{
	Head = new Node();
	End = new Node();
	Head->Next = End;
	End->Next = End;
}

void Push(int num)
{
	ptrNode = new Node();
	ptrNode->Data = num;
	ptrNode->Next = Head->Next;
	Head->Next = ptrNode;
	cout << "Push : " << num << endl;
}

int Pop(void)
{
	int result = 0;

	ptrNode = Head->Next;
	//Head->Next = ptrNode->Next;
	Head->Next = Head->Next->Next;
	result = ptrNode->Data;
	
	delete ptrNode;
	ptrNode = NULL;

	return result;
}

void DisplayStack(void)
{
	Node *indexNode = NULL;
	cout << "head -> " << ends;

	for (indexNode = Head->Next; indexNode != End; indexNode = indexNode->Next)
	{
		cout << indexNode->Data << " -> " << ends;
	}

	cout << "end" << endl;
}





