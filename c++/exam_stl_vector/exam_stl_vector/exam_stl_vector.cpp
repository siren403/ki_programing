// exam_stl_vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;


typedef vector<int *> CIntVec;
typedef CIntVec::iterator CIntVecItor;

int main()
{
	//	vector<int> v1(5,1);
	//	v1.reserve(10);
	//	//vector<int> v1;
	//
	//	v1.push_back(10);
	//	v1.push_back(11);
	//
	//
	//	cout << "요소의 개수 : " << (int)v1.size() << endl;
	//	//cout << "요소의 개수 : " << (int)v1.max_size() << endl;
	///*
	//	cout << "v1[0] = " << v1[0] << endl;
	//	cout << "v1[1] = " << v1[1] << endl;
	//*/
	//
	//
	//	//iterator : 컨테이너의 요소에 접근할 수 있는 포인터
	//	cout << "==============반복자" << endl;
	//	for (vector<int>::iterator i = v1.begin(); i != v1.end(); i++)
	//	{
	//		cout << &i << "/" << (*i) << endl;
	//	}
	//	
	//	cout << "==============반복자 역" << endl;
	//	for (vector<int>::reverse_iterator i = v1.rbegin(); i != v1.rend(); i++ )
	//	{
	//		cout << &i << "/" << (*i) << endl;
	//	}
	//
	//	cout << "==============인덱스 vector::size_type" << endl;
	//	for (vector<int>::size_type i = 0; i < v1.size(); i++)
	//	{
	//		cout << "v1[" << i << "] = " << v1[i] << endl;
	//	}
	//
	//	cout << "==============인덱스 vector::int" << endl;
	//	for (int i = 0; i < v1.size(); i++)
	//	{
	//		cout << "v1[" << i << "] = " << v1[i] << endl;
	//	}
	//
	//
	//	cout << "front : " << v1.front() << endl;
	//	cout << "back : " << v1.back() << endl;
	//
	//==============================================================================


		//1.
	/*int ti = 0;

	CIntVec tIntVec;
	tIntVec.reserve(5);

	int *tpInt = NULL;

	for (ti = 0; ti < 5; ti++)
	{
		tpInt = NULL;
		tpInt = new int();

		tIntVec.push_back(tpInt);
	}
	for (ti = 0; ti < 5; ti++)
	{
		(*tIntVec[ti]) = ti;
	}
	for (ti = 0; ti < 5; ti++)
	{
		cout << (*tIntVec[ti]) << endl;
	}
	for (ti = 0; ti < 5; ti++)
	{
		if (NULL != tIntVec[ti])
		{
			delete tIntVec[ti];
			tIntVec[ti] = NULL;
		}
	}
	tIntVec.clear();
	cout << "size : " << tIntVec.size() << endl;
	cout << "capacity : " << tIntVec.capacity() << endl;
	cout << "max size : " << tIntVec.max_size() << endl;*/

	//=======================================================

	//2.
	/*int ti = 0;

	CIntVec tIntVec;
	tIntVec.reserve(5);

	int *tpInt = NULL;

	for (ti = 0; ti < 5; ti++)
	{
		tpInt = NULL;
		tpInt = new int();
		tIntVec.push_back(tpInt);
	}

	int tVal = 0;
	for (CIntVecItor tItor = tIntVec.begin(); tItor != tIntVec.end(); tItor++)
	{
		(*(*tItor)) = tVal;
		tVal++;
	}
	for (CIntVecItor tItor = tIntVec.begin(); tItor != tIntVec.end(); tItor++)
	{
		cout << (*(*tItor)) << endl;
	}
	for (CIntVecItor tItor = tIntVec.begin(); tItor != tIntVec.end(); tItor++)
	{
		if (NULL != (*tItor))
		{
			delete (*tItor);
			(*tItor) = NULL;
		}
	}
	tIntVec.clear();
*/
//========================================================









	int tInput = 0;
	cin >> tInput;

	return 0;
}

