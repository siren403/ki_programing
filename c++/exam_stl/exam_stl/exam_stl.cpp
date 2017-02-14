// exam_stl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <queue>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>



using namespace std;

//custom queue class
class CRect
{
private:
	int mWidth = 0;
	int mHeight = 0;
public:
	CRect(int tWidth, int tHeight)
		: mWidth(tWidth), mHeight(tHeight) {}

	//오름차순
	/*bool operator<(const CRect& tRect) const
	{
		return mWidth*mHeight > tRect.mWidth*tRect.mHeight;
	}*/
	//내림차순
	bool operator<(const CRect& tRect) const
	{
		return mWidth*mHeight < tRect.mWidth*tRect.mHeight;
	}

	void Display()
	{
		cout << "CRect : " << mWidth << "*" << mHeight << "=" << mWidth*mHeight << endl;
	}

};
//custom map class
template<class F,class S>
class CValueEqual
{
private:
	S second;
public:
	CValueEqual(const S& tS) :second(tS)
	{

	}

	bool operator()(pair<const F, S> tElement)
	{
		return tElement.second == second;
	}
};

//deque
typedef deque<int> CIntDeque;
typedef CIntDeque::iterator CIntDequeItor;
typedef CIntDeque::reverse_iterator CIntDequeRItor;

//queue
typedef priority_queue<int> CPriorityQ;
typedef priority_queue<CRect, vector<CRect>, less<CRect>> CRectPriorityQ;

//map
typedef map<int, string> CMap;
typedef CMap::iterator CMapItor;
typedef CMap::value_type IsValueType;


void printDeque()
{
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
}
void printPriorityQueue()
{
	cout << "STL Priority Queue" << endl;

	CPriorityQ tPiriorityQ;

	tPiriorityQ.push(8);
	tPiriorityQ.push(1);
	tPiriorityQ.push(6);
	tPiriorityQ.push(2);

	while (!tPiriorityQ.empty())
	{
		cout << "pop : " << tPiriorityQ.top() << endl;
		tPiriorityQ.pop();
	}

}
void printCRectPriorityQueue()
{
	cout << "STL CRect priority Queue" << endl;

	CRectPriorityQ tPriorityQ;

	CRect tRect_0(1, 5);
	CRect tRect_1(7, 6);
	CRect tRect_2(1, 2);
	CRect tRect_3(8, 2);


	tPriorityQ.push(tRect_0);
	tPriorityQ.push(tRect_1);
	tPriorityQ.push(tRect_2);
	tPriorityQ.push(tRect_3);

	while (!tPriorityQ.empty())
	{
		CRect tRect = tPriorityQ.top();
		tPriorityQ.pop();

		tRect.Display();
	}

}
void printCMap()
{
	cout << "STL map" << endl;

	CMap tMap;
	CMapItor tItor;

	tMap.insert(IsValueType(100, "One Hundred"));
	tMap.insert(IsValueType(3, "Three"));
	tMap.insert(IsValueType(150, "One Hundred Fifty"));
	tMap.insert(IsValueType(99, "Ninety nine"));

	for (tItor = tMap.begin(); tItor != tMap.end(); ++tItor)
	{
		cout << "key : " << (*tItor).first << ", ";
		cout << "value : " << (*tItor).second;
		cout << endl;
	}

	cout << tMap[3].c_str() << endl;

	tMap[123] = "OneHundred Twenty Three";

	for (tItor = tMap.begin(); tItor != tMap.end(); ++tItor)
	{
		cout << "key : " << (*tItor).first << ", ";
		cout << "value : " << (*tItor).second;
		cout << endl;
	}

	tItor = tMap.find(123);
	if (tMap.end() != tItor)
	{
		tMap.erase(tItor);
	}


	for (tItor = tMap.begin(); tItor != tMap.end(); ++tItor)
	{
		cout << "key: " << (*tItor).first << ", ";
		cout << "value: " << (*tItor).second;
		cout << endl;
	}

	tItor = find_if(tMap.begin(), tMap.end(), CValueEqual<int, string>("Ninety nine"));

	if (tMap.end() != tItor)
	{
		tMap.erase(tItor);
	}

	for (tItor = tMap.begin(); tItor != tMap.end(); ++tItor)
	{
		cout << "key: " << (*tItor).first << ", ";
		cout << "value: " << (*tItor).second;
		cout << endl;
	}


	for (tItor = tMap.begin(); tItor != tMap.end();)
	{
		if ("Three" == tItor->second)
		{
			tItor = tMap.erase(tItor);
		}
		else
		{
			++tItor;
		}
	}


	for (tItor = tMap.begin(); tItor != tMap.end(); ++tItor)
	{
		cout << "key: " << (*tItor).first << ", ";
		cout << "value: " << (*tItor).second;
		cout << endl;
	}
}

int main()
{
	//printDeque();
	//printPriorityQueue();
	//printCRectPriorityQueue();
	printCMap();
    return 0;
}


