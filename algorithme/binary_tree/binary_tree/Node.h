#pragma once
class Node
{
private:
	char mData = 0;
	Node *mLeft = NULL;
	Node *mRight = NULL;
public:
	Node();
	~Node();
	
	void SetData(char tData);
	char GetData();

	void SetLeft(Node *tLeft);
	Node* GetLeft();

	void SetRight(Node *tRight);
	Node* GetRight();
};

