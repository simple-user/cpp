#pragma once
#include <iostream>
#include <ctime>
#include "Account.h"

enum sex { MALE, FEMALE };
const int DATE_STR_LEN = 11;

class Person
{
private:
	char *Fam;
	char *Imn;
	char *Otc;
	tm Dr;
	char *DrStr;
	sex Sex;
	char *PhoneNumber;
	Account Person_account;

	void assign(const char *fam, const char *imn, const char *otc, const sex _sex, const char *phoneNumber);
	inline void strInput(char *&Dest, const char *Sorce);
	inline bool makeDateFromStr(const char* dr);
	inline bool makePhoneFromStr(const char* dr);
	bool dateInput(const char dr);
	inline void movePerson(Person & p);
	inline char* getCopyOfStr(const char* str) const;
public:
	Person() = delete;
	Person(const Person& p) = delete;
	Person & operator=(const Person& p) = delete;
	Person & operator=(Person&& p) = delete;
	
	Person(Person&& p);
	Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber, Account&& account);
	Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber, 
		   const char* account_nom, char account_curr[], int account_moneySum);

	
	
	friend std::ostream& operator<<(std::ostream &os, const Person& p);
	
	void Print() const;
	
	Account * accountData();

	const char* getFam() const;
	char* getCopyFam() const;
	const char* getImn() const;
	char* getCopyImn() const;
	const char* getOtc() const;
	char* getCopyOtc() const;
	const tm& getDr() const;
	tm getCopyDr() const;
	const char* getStringDr() const;
	char* getCopyStringDr() const;
	bool isBoy() const;
	const char* getPhoneNumber() const;
	char* getCopyPhoneNumber() const;

	void setFam(const char *fam); 	
	void setImn(const char *imn);
	void setOtc(const char *otc);
	bool setDr(const char *dr); // 1-good, 0-fail
	bool setSex(const sex _sex);
	bool setPhoneNumber(const char* phoneNumber);

	~Person();
};

