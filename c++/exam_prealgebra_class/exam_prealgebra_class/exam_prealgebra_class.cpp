// exam_prealgebra_class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class CPreAlgebra
{
private:
	float mResult = 0.0f;
public:
	CPreAlgebra();
	~CPreAlgebra();
	void SetResult(float tResult);
	float GetResult();
	void DoAddictive(float tA, float tB);
	void DoSubtract(float tA, float tB);
	void DoMultiply(float tA, float tB);
	void DoDivide(float tA, float tB);

};



int main()
{
	float tA = 0;
	float tB = 0;
	CPreAlgebra tPreAlgebra;

	tA = 3;
	tB = 2;



	//DoAddictive
	//tResult = tA + tB;
	tPreAlgebra.DoAddictive(tA, tB);
	cout << tPreAlgebra.GetResult() << endl;

	//DoSubtract
	tPreAlgebra.DoSubtract(tA, tB);
	cout << tPreAlgebra.GetResult() << endl;

	//DoMultiply
	tPreAlgebra.DoMultiply(tA, tB);
	cout << tPreAlgebra.GetResult() << endl;

	//DoDivide
	tPreAlgebra.DoDivide(tA, tB);
	cout << tPreAlgebra.GetResult() << endl;

	return 0;
}

void CPreAlgebra::DoAddictive(float tA, float tB)
{
	mResult = tA + tB;
}

void CPreAlgebra::DoSubtract(float tA, float tB)
{
	mResult = tA - tB;
}

void CPreAlgebra::DoMultiply(float tA, float tB)
{
	mResult = tA * tB;
}

void CPreAlgebra::DoDivide(float tA, float tB)
{
	mResult = tA / tB;
}

CPreAlgebra::CPreAlgebra()
{
	mResult = 0.0f;
}

CPreAlgebra::~CPreAlgebra()
{

}

void CPreAlgebra::SetResult(float tResult)
{
	mResult = tResult;
}

float CPreAlgebra::GetResult()
{
	return mResult;
}
