#pragma once

#include "Stack.h"

class Tree
{
private:
	Node* mParent = NULL;
	Node* mLeftChild = NULL;
	Node* mRightChild = NULL;

	Node* mHeadNode = NULL;
	Node* mEndNode = NULL;

	Stack* mStack = NULL;
public:
	Tree();
	~Tree();

	void MakeTree();
	void Traverse(Node *ptrNode);
	void Visit(Node *);
};

