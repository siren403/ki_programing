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
	
	void Traverse();//전위 순회

	void RecursiveTraverse(Node *ptrNode);//재귀호출
	
	//중위 순회
	void MediumStackTraverse();//스택

	//후위 순회
	void RearStackTraverse();//스택

	void Visit(Node *);

	Node *GetHeadNode();
};

