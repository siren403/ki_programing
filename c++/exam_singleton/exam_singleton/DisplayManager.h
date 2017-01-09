#pragma once
class CDisplayManager
{
private:
	
	static CDisplayManager *pInstance;

	CDisplayManager();
	~CDisplayManager();
public:

	static CDisplayManager* GetInstance();

	void Display();
	//이렇게 해제 할 시 외부에서 별도로 호출해줘야 한다.
	//관리 부담 증가
	//인스턴스 생성시에 
	/*
	atexit(release_instance); : 
		return type과 parameter가 모두 void인 함수 포인터를 전달받는 함수이며,
		종료할 때 지정된 함수를 처리한다고 합니다. 또한 해당 API는 최대 32개까지 
		추가할 수 있으며 LIFO 형태로 마지막에 들어온 함수가 가장 먼저 실행된다.
	*/
	//함수에 자원해제 함수를 등록하여 종료 시 별도 호출 없이 자원해제

	void Destroy();
};

