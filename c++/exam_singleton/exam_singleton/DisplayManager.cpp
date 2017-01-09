#include "stdafx.h"
#include "DisplayManager.h"
#include <iostream>

using namespace std;

CDisplayManager *CDisplayManager::pInstance = NULL;

CDisplayManager::CDisplayManager()
{

}

CDisplayManager::~CDisplayManager()
{

}

CDisplayManager * CDisplayManager::GetInstance()
{
	if (NULL == pInstance)
	{
		pInstance = new CDisplayManager();
		cout << "Create Display Manager" << endl;
	}
	return pInstance;
}

void CDisplayManager::Display()
{
	cout << "display" << endl;
}

void CDisplayManager::Destroy()
{
	/*delete pInstance;
	pInstance = NULL;
	delete this;
*/
	cout << "Destroy Manager" << endl;

	//pInstance->Display();
}
