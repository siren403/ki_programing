#include "stdafx.h"
#include "Tree.h"

#include <iostream>

using namespace std;

Tree::Tree()
{
	mHeadNode = new Node();
	mEndNode = new Node();
	mStack = new Stack();

	mHeadNode->SetLeft(mEndNode);
	mHeadNode->SetRight(mEndNode);

	mEndNode->SetLeft(mEndNode);
	mEndNode->SetRight(mEndNode);

	mStack->InitializeStack();
}


Tree::~Tree()
{
	if (mParent != NULL)
	{
		delete mParent;
		mParent = NULL;
	}
	if (mLeftChild != NULL)
	{
		delete mLeftChild;
		mLeftChild = NULL;
	}
	if (mRightChild != NULL)
	{
		delete mRightChild;
		mRightChild = NULL;
	}
	if (mHeadNode != NULL)
	{
		delete mHeadNode;
		mHeadNode = NULL;
	}
	if (mEndNode != NULL)
	{
		delete mEndNode;
		mEndNode = NULL;
	}
	if (mStack != NULL)
	{
		delete mStack;
		mStack = NULL;
	}

}

void Tree::MakeTree()
{
	mParent = new Node();
	mParent->SetData('A');

	mLeftChild = new Node();
	mLeftChild->SetData('B');

	mRightChild = new Node();
	mRightChild->SetData('C');


	mParent->SetLeft(mLeftChild);
	mParent->SetRight(mRightChild);
	mHeadNode->SetLeft(mParent);
	mHeadNode->SetRight(mParent);
	mParent = mParent->GetLeft();

	/*===================
			   Head
			 
			'A'(Root)
		'B'(*)		  'C'
	=====================*/

	mLeftChild = new Node();
	mLeftChild->SetData('D');
	mLeftChild->SetLeft(mEndNode);
	mLeftChild->SetRight(mEndNode);

	mRightChild = new Node();
	mRightChild->SetData('E');
	mRightChild->SetLeft(mEndNode);
	mRightChild->SetRight(mEndNode);
	
	mParent->SetLeft(mLeftChild);
	mParent->SetRight(mRightChild);
	mParent = mHeadNode->GetRight()->GetRight();

	/*=====================
	
	=====================*/
	mLeftChild = new Node();
	mLeftChild->SetData('F');
	mLeftChild->SetLeft(mEndNode);
	mLeftChild->SetRight(mEndNode);
	
	mRightChild = new Node();
	mRightChild->SetData('G');
	mRightChild->SetLeft(mEndNode);
	mRightChild->SetRight(mEndNode);

	mParent->SetLeft(mLeftChild);
	mParent->SetLeft(mRightChild);

}

void Tree::Traverse(Node * ptrNode)
{
	mStack->Push(ptrNode);

	while (!mStack->IsStackEmpty())
	{
		ptrNode = mStack->Pop();
		Visit(ptrNode);

		if (ptrNode->GetRight() != mEndNode)
		{
			mStack->Push(ptrNode->GetRight());
		}

		if (ptrNode->GetLeft() != mEndNode)
		{
			mStack->Push(ptrNode->GetLeft());
		}
	}
}

void Tree::Visit(Node *ptrNode)
{
	cout << ptrNode->GetData() << " -> " << endl;
}
