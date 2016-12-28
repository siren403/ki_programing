#pragma once

#include "Node.h"

#define MAX 100


class Stack
{
private:
	Node *mStackArray[MAX];//스택을 배열로 선언
	int mTop = 0;

public:
	Stack();
	~Stack();

	void InitializeStack();
	void Push(Node *);
	Node* Pop();
	bool IsStackEmpty();
};

