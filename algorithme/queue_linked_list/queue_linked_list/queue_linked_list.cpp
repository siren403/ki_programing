// queue_linked_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node
{
	int mKey = 0;
	Node * mpPrev = nullptr;
	Node * mpNext = nullptr;
};

Node * mpHead = nullptr;
Node * mpTail = nullptr;


void init_queue()
{
	mpHead = new Node();
	mpTail = new Node();

	mpHead->mpPrev = mpHead;
	mpHead->mpNext = mpTail;

	mpTail->mpPrev = mpHead;
	mpTail->mpNext = mpTail;
}


void clear_queue()
{
	Node * t = nullptr;
	Node * s = nullptr;

	t = mpHead->mpNext;

	while (t != mpTail)
	{
		s = t;
		t = t->mpNext;

		delete s;
	}

	mpHead->mpNext = mpTail;
	mpTail->mpPrev = mpHead;
}

int put(int k)
{
	Node * t = nullptr;

	t = new Node();
	if (t == nullptr)
	{
		printf("\n    Out of memory.");
		return -1;
	}

	t->mKey = k;
	mpTail->mpPrev->mpNext = t;
	t->mpPrev = mpTail->mpPrev;
	mpTail->mpPrev = t;
	t->mpNext = mpTail;

	return k;
}


int get()
{
	Node * t = nullptr;
	int i = 0;

	t = mpHead->mpNext;

	if (t == mpTail)
	{
		printf("\n    Queue underflow.");
		return -1;
	}

	i = t->mKey;

	mpHead->mpNext = t->mpNext;
	t->mpNext->mpPrev = mpHead;

	delete t;

	return i;
}

void print_queue(void)
{
	Node * t = NULL;

	t = mpHead->mpNext;

	printf("\n  Queue contents : Front ----> Rear\n");
	while (t != mpTail)
	{
		printf("%-6d", t->mKey);

		t = t->mpNext;
	}
}

int main()
{
	
	int i = 0;
	init_queue();

	printf("\nPut 5, 4, 7, 8, 2, 1");
	put(5);
	put(4);
	put(7);
	put(8);
	put(2);
	put(1);
	print_queue();

	printf("\nGet");
	i = get();
	print_queue();
	printf("\n   getting value is %d", i);

	printf("\nPut 3, 2, 5, 7");
	put(3);
	put(2);
	put(5);
	put(7);
	print_queue();

	printf("\nPut 3");
	put(3);
	print_queue();

	printf("\nInitialize queue");
	clear_queue();
	print_queue();

	printf("\nNow queue is empty, get");
	i = get();
	print_queue();
	printf("\n   getting value is %d", i);

	return 0;
}


