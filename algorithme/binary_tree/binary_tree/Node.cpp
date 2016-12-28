#include "stdafx.h"
#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

char Node::GetData()
{
	return this->mData;
}

void Node::SetData(char tData)
{
	this->mData = tData;
}

void Node::SetLeft(Node * tLeft)
{
	this->mLeft = tLeft;
}

Node * Node::GetLeft()
{
	return this->mLeft;
}

void Node::SetRight(Node * tRight)
{
	this->mRight = tRight;
}

Node * Node::GetRight()
{
	return this->mRight;
}
