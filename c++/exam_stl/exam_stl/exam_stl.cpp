// exam_stl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <iostream>

using namespace std;

//deque
typedef deque<int> CIntDeque;
typedef CIntDeque::iterator CIntDequeItor;
typedef CIntDeque::reverse_iterator CIntDequeRItor;

int main()
{

#pragma region deque
	cout << "STL deque" << endl;

	CIntDeque tIntDeque;
	CIntDequeItor tItor;
	CIntDequeRItor tRItor;

	tIntDeque.push_front(3);
	tIntDeque.push_front(2);
	tIntDeque.push_front(1);

	tIntDeque.push_back(33);
	tIntDeque.push_back(22);
	tIntDeque.push_back(11);


	cout << "begin : end" << endl;
	for (tItor = tIntDeque.begin(); tItor != tIntDeque.end(); ++tItor)
	{
		cout << "element value : " << *tItor << endl;
	}
	
	cout << "rbegin : rend" << endl;
	for (tRItor = tIntDeque.rbegin(); tRItor != tIntDeque.rend(); ++tRItor)
	{
		cout << "element value : " << *tRItor << endl;
	}

	cout << tIntDeque[3] << endl;

	tIntDeque.push_front(777);
	tIntDeque.push_back(888);

	cout << "push front : 777, push back : 888" << endl;
	for (tItor = tIntDeque.begin(); tItor != tIntDeque.end(); ++tItor)
	{
		cout << "element value : " << *tItor << endl;
	}

	tIntDeque.pop_front();
	tIntDeque.pop_back();
	cout << "pop front, pop back" << endl;
	for (tItor = tIntDeque.begin(); tItor != tIntDeque.end(); ++tItor)
	{
		cout << "element value : " << *tItor << endl;
	}

	if (!tIntDeque.empty())
	{
		cout << tIntDeque.front() << endl;
		cout << tIntDeque.back() << endl;
	}
#pragma endregion

    return 0;
}

