#include "stdafx.h"
#include "Stack.h"

#include <iostream>

using namespace std;

Stack::Stack()
{
}


Stack::~Stack()
{
}

void Stack::InitializeStack()
{
	this->mTop = 0;
}

void Stack::Push(Node *ptrNode)
{
	mStackArray[mTop] = ptrNode;
	mTop = (mTop++) % MAX;//??
	cout << "mTop : " << mTop << endl;
}

Node* Stack::Pop()
{
	Node *ptrNode = NULL;

	if (!IsStackEmpty())
	{
		ptrNode = mStackArray[--mTop];
		return ptrNode;
	}
	else
	{
		cout << "Stack is Empty" << endl;
	}

	return NULL;
}

bool Stack::IsStackEmpty()
{
	if (mTop == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
