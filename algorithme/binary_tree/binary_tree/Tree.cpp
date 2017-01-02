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
	mParent->SetRight(mRightChild);

}

void Tree::Traverse()
{
	Node *ptrNode = mHeadNode->GetLeft();

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

void Tree::RecursiveTraverse(Node *ptrNode)
{
	//Node *ptrNode = mHeadNode->GetLeft();
	if (ptrNode != mEndNode)
	{
		RecursiveTraverse(ptrNode->GetLeft());
		//Visit(ptrNode);//중위
		RecursiveTraverse(ptrNode->GetRight());
		Visit(ptrNode);//후위
	}
}

void Tree::MediumStackTraverse()
{
	int Finish = 0;
	Node *ptrNode = mHeadNode->GetLeft();
	do 
	{
		while (ptrNode != mEndNode)
		{
			mStack->Push(ptrNode);
			ptrNode = ptrNode->GetLeft();
		}

		if (!mStack->IsStackEmpty())
		{
			ptrNode = mStack->Pop();
			Visit(ptrNode);
			ptrNode = ptrNode->GetRight();
		}
		else
		{
			Finish = 1;
		}
	} while (!Finish);
}




void Tree::RearStackTraverse()
{
	int finish = 0;
	Node *ptrNode = mHeadNode->GetLeft();
	Node *ptrVisited = mEndNode;
	Node *ptrPushed = mEndNode;

	do
	{
		while (ptrNode != mEndNode && ptrNode != ptrVisited)
		{
			if (ptrNode != ptrPushed)
			{
				mStack->Push(ptrNode);
			}

			if (ptrNode->GetRight() != mEndNode)
			{
				mStack->Push(ptrNode->GetRight());
			}
			if (ptrNode->GetLeft() != mEndNode)
			{
				mStack->Push(ptrNode->GetLeft());
			}

			ptrPushed = ptrNode->GetLeft();
			ptrNode = ptrNode->GetLeft();
		}
	
		if (!mStack->IsStackEmpty())
		{
			ptrNode = mStack->Pop();

			if (ptrNode->GetLeft() != mEndNode && ptrNode->GetRight() == mEndNode &&
				ptrNode->GetLeft() != ptrVisited)
			{
				mStack->Push(ptrNode);
				ptrNode = ptrNode->GetLeft();
			}

			if (ptrNode->GetRight() == mEndNode || ptrNode->GetRight() == ptrVisited)
			{
				Visit(ptrNode);
				ptrVisited = ptrNode;
			}
		}
		else
		{
			finish = 1;
		}

	} while (!finish);

}

void Tree::Visit(Node *ptrNode)
{
	cout << ptrNode->GetData() << " -> " << ends;
}

Node * Tree::GetHeadNode()
{
	return mHeadNode;
}
