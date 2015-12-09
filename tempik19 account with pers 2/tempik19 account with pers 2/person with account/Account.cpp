#include <iostream>
#include "Account.h"

//Account(const Account&) = delete;

//Account(const char* nom, char curr[], int moneySum);
Account::Account(const char *nom, char curr[], int moneySum) : Nom(nullptr), MoneySum(moneySum), Len_nom(strlen(nom))
{
	if (MoneySum<0) exit(EXIT_FAILURE);
	Nom = new char[Len_nom+1];
	Curr = new char[4];
	strcpy_s(Nom,Len_nom+1,nom);
	strcpy_s(Curr,4, curr); // якщо більше 3 символів - вилетить :(
}

//Account(Account&& a);
Account::Account(Account &&a) : Nom(a.Nom), Len_nom(a.Len_nom), MoneySum(a.MoneySum), Curr(a.Curr)
{
	a.Nom = nullptr;
	a.Curr = nullptr;
}

//bool takeMoney(const char curr[], int moneySumTake);
bool Account::takeMoney(const char curr[], int moneySumTake)
{
	if (MoneySum<moneySumTake || _stricmp(curr,Curr))
		return 0; // нєуспєх

	MoneySum-=moneySumTake;
	return 1;
}

//bool addMoney(const char curr[], int moneySumAdd);
bool Account::addMoney(const char curr[], int moneySumAdd)
{
	if (_stricmp(curr,Curr))
		return 0; // fail

	MoneySum+=moneySumAdd;
	return 1;
}

//bool transferTo(Account & a, int moneySumTrans);
bool Account::transferTo(Account &a, int moneySumTrans)
{
	if (_stricmp(Curr,a.Curr))
		return 0;

	if (!takeMoney(Curr,moneySumTrans))
		return 0;

	if(!a.addMoney(Curr,moneySumTrans))
	{
		addMoney(Curr,moneySumTrans);
		return 0;
	}
	return 1;
}

//void ShowInfa();
void Account::ShowInfa() const
{
	std::cout << "Account: nom=" << Nom << ",  curr=" << Curr << ", moneySum=" << double(MoneySum)/100 << std::endl;
}

//
//~Account(void);
Account::~Account()
{
	if(Nom)
		delete[] Nom;

	if(Curr)
		delete[] Curr;
	
}