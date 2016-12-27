// exam_constructor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class OrangeBox
{
private:
	int total;
public:
	OrangeBox()
	{
		cout << "神兄走 持失" << endl;
	}
	~OrangeBox()
	{
		cout << "神兄走 社瑚" << endl;
	}
	void Add(int num);
	void Del(int num);
	void Empty();
	int GetTotal()
	{
		return total;
	}
};
void NewStack();

int main()
{
	NewStack();

	cout << "=======" << endl;


	OrangeBox obox;
	obox.Empty();
	obox.Add(5);
	obox.Del(4);
	int nResult = obox.GetTotal();
	cout << nResult << endl;

	OrangeBox *obox1 = NULL;
	obox1 = new OrangeBox();

	cout << "=======" << endl;

	delete obox1;

    return 0;
}

void NewStack()
{
	OrangeBox obox;
}

void OrangeBox::Add(int num)
{
	total += num;
}
void OrangeBox::Del(int num)
{
	total -= num;
	if (total < 0)
	{
		Empty();
	}
}
void OrangeBox::Empty()
{

	total = 0;
}
