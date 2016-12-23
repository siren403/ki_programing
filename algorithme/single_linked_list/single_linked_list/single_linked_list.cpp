// single_linked_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node
{
	char mData = 0;
	Node *Next = NULL;
};

void InsertNode(Node *tpNode, Node *tpHead, Node *tpEnd);
void DeleteNode(Node *tpNode, Node *tpHead, Node *tpEnd);

int main()
{
	Node *tHead = NULL;
	Node *tEnd = NULL;
	Node *tTemp = NULL;

	Node *tTemp1 = NULL;
	Node *tTemp2 = NULL;
	Node *tTemp3 = NULL;
	Node *tTemp4 = NULL;


	Node *tpPtr = NULL;
	tHead = new Node();
	tEnd = new Node();


	tTemp1 = new Node();
	tTemp1->mData = 'A';
	//Head->tTemp1('A')->tEnd(->tEnd)
	tHead->Next = tTemp1;
	tTemp1->Next = tEnd;
	tEnd->Next = tEnd;
	tpPtr = tTemp1;

	tTemp2 = new Node();
	tTemp2->mData = 'B';
	//Head->tTemp1('A')->tTemp2('B')->tEnd
	tpPtr->Next = tTemp2;
	tTemp2->Next = tEnd;
	tpPtr = tTemp2;

	tTemp3 = new Node();
	tTemp3->mData = 'D';
	//Head->tTemp1('A')->tTemp2('B')->tTemp3('D')->tEnd
	tpPtr->Next = tTemp3;
	tTemp3->Next = tEnd;
	tpPtr = tTemp3;

	tTemp4 = new Node();
	tTemp4->mData = 'E';
	//Head->tTemp1('A')->tTemp2('B')->tTemp3('D')->tTemp4('E')->tEnd
	tpPtr->Next = tTemp4;
	tTemp4->Next = tEnd;
	tpPtr = tTemp4;


	//링크드 리스트의 노드에 저장된 데이터 출력
	tpPtr = tHead->Next;
	int ti = 0;
	for (ti = 0; ti < 4; ti++)
	{
		printf("%2c", tpPtr->mData);
		tpPtr = tpPtr->Next;
	}
	cout << endl;

	//새로운 노드 생성
	tTemp = new Node();
	tTemp->mData = 'C';

	//새로 생성한 노드 삽입
	InsertNode(tTemp, tHead, tEnd);

	//링크드 리스트의 노드에 저장된 데이터 출력
	tpPtr = tHead->Next;
	for (ti = 0; ti < 5; ti++)
	{
		printf("%2c", tpPtr->mData);
		tpPtr = tpPtr->Next;
	}
	cout << endl;

	DeleteNode(tTemp, tHead, tEnd);
	tTemp = NULL;


	//링크드 리스트의 노드에 저장된 데이터 출력
	cout << "C노드 삭제 후" << endl;
	tpPtr = tHead->Next;
	for (ti = 0; ti < 4; ti++)
	{
		printf("%2c", tpPtr->mData);
		tpPtr = tpPtr->Next;
	}
	cout << endl;
	return 0;
}

void InsertNode(Node *tpNode, Node *tpHead, Node *tpEnd)
{
	Node *tpIndex = NULL;

	for (tpIndex = tpHead; tpIndex != tpEnd; tpIndex = tpIndex->Next)
	{
		if (tpIndex->mData<tpNode->mData&&tpIndex->Next->mData > tpNode->mData)
			break;
	}

	tpNode->Next = tpIndex->Next;
	tpIndex->Next = tpNode;
}

void DeleteNode(Node *tpNode, Node *tpHead, Node *tpEnd)
{
	Node *tpIndex = NULL;
	Node *tpDelete = NULL;


	for (tpIndex = tpHead; tpIndex != tpEnd; tpIndex = tpIndex->Next)
	{
		if (tpIndex->Next->mData == tpNode->mData)
		{
			tpDelete = tpIndex->Next;
			break;
		}
	}

	tpIndex->Next = tpIndex->Next->Next;
	delete tpDelete;
}
