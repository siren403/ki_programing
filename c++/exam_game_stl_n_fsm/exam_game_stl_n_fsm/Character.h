#pragma once

class Character
{
protected:
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;


public:
	Character();
	virtual ~Character();

	//getter
	int GetHealth();
	int& GetCurrentHealth();
	int& GetPower();
	//setter
	void SetHealth(int tHealth);
	void SetCurrentHealth(int tCurHealth);
	void SetPower(int tPower);

	void DoAttack(Character *tTarget);
	
};

