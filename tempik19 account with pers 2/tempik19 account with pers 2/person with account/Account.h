#ifndef _ACCOUNT_
#define _ACCOUNT_

class Account
{
private:
	char *Nom;
	int Len_nom;
	int MoneySum;
	char *Curr;
public:
	
	Account(const Account&) = delete;
	Account(Account&& a);
	Account(const char* nom, char curr[], int moneySum);
	
	Account& operator=(Account && a) = delete;
	
	
	bool takeMoney(const char curr[], int moneySumTake); // 0-fail, 1-good
	bool addMoney(const char curr[], int moneySumAdd); //0-fail(currency), 1-good
	bool transferTo(Account & a, int moneySumTrans);

	void ShowInfa() const;

	~Account(void);
};

#endif


