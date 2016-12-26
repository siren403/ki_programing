// double_linked_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node
{
	char Data = 0;
	Node *Next = NULL;
	Node *Prev = NULL;
};

Node *tHead, *tEnd, *temp;
Node *temp1, *temp2, *temp3, *temp4;

void Initialize(void);
void InsertNode(Node *);
void DeleteNode(Node *);

int main()
{
	Node *ptr = NULL;
	int i = 0;
	Initialize();

	cout << "노드 C의 삽입 전 " << endl;
	ptr = tHead->Next;

	for (i = 0; i < 4; i++)
	{
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	//삽입할 새로운 노드 생성
	temp = new Node();
	temp->Data = 'C';

	//노드의 삽입
	InsertNode(temp);

	cout << "노드 C의 삽입 후 " << endl;
	ptr = tHead->Next;

	for (i = 0; i < 5; i++)
	{
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	//노드의 삭제
	DeleteNode(temp);


	cout << "노드 C의 삭제 후 " << endl;
	ptr = tHead->Next;

	for (i = 0; i < 4; i++)
	{
		cout << ptr->Data;
		ptr = ptr->Next;
	}

    return 0;
}

void Initialize(void)
{

	Node *ptr = NULL;

	tHead = new Node();
	tEnd = new Node();

	//h<->1->e(->e)
	temp1 = new Node();
	temp1->Data = 'A';
	tHead->Next = temp1;
	temp1->Next = tEnd;//다음 노드와
	temp1->Prev = tHead;//이전 노드연결
	tEnd->Next = tEnd;//End는 자기 자신 연결

	ptr = temp1;

	temp2 = new Node();
	temp2->Data = 'B';
	ptr->Next = temp2;//이전 노드가 가리키던 End노드 대신 새로 생성한 temp2연결
	temp2->Next = tEnd;//temp2의 Next에 End연결
	temp2->Prev = ptr;

	ptr = temp2;

	temp3 = new Node();
	temp3->Data = 'D';
	ptr->Next = temp3;
	temp3->Next = tEnd;
	temp3->Prev = ptr;

	ptr = temp3;

	temp4 = new Node();
	temp4->Data = 'E';
	ptr->Next = temp4;
	temp4->Next = tEnd;
	temp4->Prev = ptr;

	ptr = temp4;

}

void InsertNode(Node *ptr)
{
	Node *indexptr = NULL;
	
	for (indexptr = tHead->Next; indexptr != tEnd; indexptr = indexptr->Next)
	{
		if (indexptr->Data < ptr->Data && indexptr->Next->Data > ptr->Data)
		{
			break;
		}
	}
	ptr->Next = indexptr->Next;
	indexptr->Next->Prev = ptr;

	indexptr->Next = ptr;
	ptr->Prev = indexptr;
}

void DeleteNode(Node *ptr)
{

	Node *indexptr = NULL;
	Node *deleteptr = NULL;

	for (indexptr = tHead; indexptr != tEnd; indexptr = indexptr->Next)
	{
		if (indexptr->Next->Data == ptr->Data)
		{
			deleteptr = indexptr->Next;
			break;
		}
	}

	indexptr->Next = indexptr->Next->Next;
	indexptr->Next->Next->Prev = indexptr;
	
	delete deleteptr;
}
