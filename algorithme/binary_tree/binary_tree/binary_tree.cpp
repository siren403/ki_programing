// binary_tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"

#include <iostream>

using namespace std;

int main()
{
	Tree tTree;

	tTree.MakeTree();
	//tTree.Traverse();

	tTree.RecursiveTraverse(tTree.GetHeadNode()->GetLeft());
	cout << endl;
	tTree.StackTraverse();


    return 0;
}

