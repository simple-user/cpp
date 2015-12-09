#include <iostream>
#include "Person.h"

using namespace std;


//inline void strInput(char *Dest, const char *Sorce);
inline void Person::strInput(char *&Dest, const char *Sorce)
{
	if (Dest)
		delete[] Dest;

	if (Sorce)
	{
		int tempLen = strlen(Sorce) + 1;
		Dest = new char[tempLen];
		strcpy_s(Dest, tempLen, Sorce);
	}
	else
		Dest = nullptr;
}


//inline void makeDateFromPerson(const char* dr);
inline bool Person::makeDateFromStr(const char* dr)
{
	bool uspeh = 0;

	if (DrStr)
	{
		delete[] DrStr;
		DrStr = nullptr;
	}

	if (dr && (strlen(dr) + 1) == DATE_STR_LEN)
	{
		tm drT = {};
		char drStr[DATE_STR_LEN] = {};
		strcpy_s(drStr, DATE_STR_LEN, dr);
		char *c = nullptr;
		char *c2 = nullptr;
		int n[3] = {};
		c = strtok_s(drStr, ".", &c2);
		for (int a = 0; a < 3 && c; a++)
		{
			n[a] = atoi(c);
			c = strtok_s(0, ".", &c2);
		}
		Dr.tm_mday = n[0];
		Dr.tm_mon = n[1] - 1;
		Dr.tm_year = n[2] - 1900;
		drT = Dr;
		mktime(&drT);
		if (drT.tm_mday != Dr.tm_mday || drT.tm_mon != Dr.tm_mon || drT.tm_year != Dr.tm_year || Dr.tm_year < 0 || Dr.tm_mon < 0 || Dr.tm_mday < 1)
			Dr = { 0 };
		else
		{
			DrStr = new char[DATE_STR_LEN];
			strcpy_s(DrStr, DATE_STR_LEN, dr);
			uspeh = 1;
		}
	}

	return uspeh;
}

// inline bool makePhoneFromStr(const char* dr);
inline bool Person::makePhoneFromStr(const char* phoneNumber)
{
	bool uspeh = 0;

	if (PhoneNumber)
	{
		delete[] PhoneNumber;
		PhoneNumber = nullptr;
	}
	// +38|097|1234567|
	// 123 456 7890123 
	if ((phoneNumber[0] == '+' && strlen(phoneNumber) == 13) || (phoneNumber[0] == '0' && strlen(phoneNumber) == 10))  
	{
		PhoneNumber = new char[strlen(phoneNumber) + 1];
		strcpy_s(PhoneNumber, strlen(phoneNumber) + 1, phoneNumber);
		uspeh = 1;
	}
	return uspeh;
}


//	void assign(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber);
void Person::assign(const char *fam, const char *imn, const char *otc, const sex _sex, const char *phoneNumber)
{
	int tempLen = 0;

	Sex = _sex;
	
	strInput(Fam, fam);
	strInput(Imn, imn);
	strInput(Otc, otc);
}

//Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber, Account&& account);
Person::Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber, Account&& account)
: Fam(nullptr), Imn(nullptr), Otc(nullptr), DrStr(nullptr), PhoneNumber(nullptr), Person_account(move(account))
{
	assign(fam, imn, otc,_sex, phoneNumber);
	makeDateFromStr(dr);
	makePhoneFromStr(phoneNumber);
}

//	Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber, 
//         const char* account_nom, char account_curr[], int account_moneySum);
Person::Person(const char *fam, const char *imn, const char *otc, const char* dr, const sex _sex, const char *phoneNumber,
	           const char* account_nom, char account_curr[], int account_moneySum)
			   : Fam(nullptr), Imn(nullptr), Otc(nullptr), DrStr(nullptr), PhoneNumber(nullptr), Person_account(account_nom, account_curr, account_moneySum)
{
	assign(fam, imn, otc, _sex, phoneNumber);
	makeDateFromStr(dr);
	makePhoneFromStr(phoneNumber);
}

//inline void movePerson(Person & p);
inline void Person::movePerson(Person &p)
{
	Fam = p.Fam;
	Imn = p.Imn;
	Otc = p.Otc;
	Dr = p.Dr;
	DrStr = p.DrStr;
	Sex = p.Sex;
	PhoneNumber = p.PhoneNumber;
	p.Fam = nullptr;
	p.Imn = nullptr;
	p.Otc = nullptr;
	p.DrStr = nullptr;
	p.PhoneNumber = nullptr;
}

//Person(Person&& p);
Person::Person(Person &&p) : Person_account(move(p.Person_account))
{
	movePerson(p);
}

//friend std::ostream& operator<<(std::ostream &os, const Person& p);
ostream& operator<<(ostream &os, const Person& p)
{
	p.Print();
	return os;
}


//void Print() const;
void Person::Print() const
{
	cout << "Information about person:\n";
	cout << "Full name: " << (Fam ? Fam : "no info") << " " << (Imn ? Imn : "no Info") <<
		    " " << (Otc ? Otc : "no Info" ) << endl;
	cout << "Sex: " << (Sex == MALE ? "male" : "female") << endl;
	cout << (Sex == MALE ? "He" : "She") << " was born: " << (DrStr ? DrStr : "no Info") << endl;
	cout << "phone number: " << ( PhoneNumber ? PhoneNumber : "no info") << endl;
	Person_account.ShowInfa();
}

//Account * accountData();
Account * Person::accountData()
{
	return &Person_account;
}

//const char* getFam() const;
const char* Person::getFam() const
{
	return Fam;
}

//	inline char* getCopyOfStr(const char* str) const;
inline char* Person::getCopyOfStr(const char* str) const
{
	char *famTemp = nullptr;
	if (str)
	{
		famTemp = new char[strlen(str) + 1];
		strcpy_s(famTemp, strlen(str) + 1, Fam);
	}

	return famTemp;
}

//char* getCopyFam() const;
char* Person::getCopyFam() const
{
	return getCopyOfStr(Fam);
}

//const char* getImn() const;
const char* Person::getImn() const
{
	return Imn;
}

//char* getCopyImn() const;
char* Person::getCopyImn() const
{
	return getCopyOfStr(Imn);
}

//const char* getOtc() const;
const char* Person::getOtc() const
{
	return Otc;
}

//char* getCopyOtc() const;
char* Person::getCopyOtc() const
{
	return getCopyOfStr(Otc);
}

//const tm& getDr() const;
const tm& Person::getDr() const
{
	return Dr;
}

//const tm getCopyDr() const;
 tm Person::getCopyDr() const
{
	return Dr;
}

//char* getStringDr() const;
const char* Person::getStringDr() const
{
	return DrStr;
}

//char* getCopyStringDr() const;
char* Person::getCopyStringDr() const
{
	return getCopyOfStr(DrStr);
}

//bool isBoy() const;
bool Person::isBoy() const
{
	return Sex == MALE;
}

//const char* getPhoneNumber() const;
const char* Person::getPhoneNumber() const
{
	return PhoneNumber;
}

//char* getCopyPhoneNumber() const;
char* Person::getCopyPhoneNumber() const
{
	return getCopyOfStr(PhoneNumber);
}

//void setFam(const char *fam);
void Person::setFam(const char *fam)
{
	strInput(Fam, fam);
}

//void setImn(const char *imn);
void Person::setImn(const char *imn)
{
	strInput(Imn, imn);
}

//void setOtc(const char *otc);
void Person::setOtc(const char *otc)
{
	strInput(Otc, otc);
}

//bool setDr(const char *dr); // 1-good, 0-fail
bool Person::setDr(const char *dr)
{
	return makeDateFromStr(dr);
}

//bool setSex(const sex _sex);
bool Person::setSex(const sex _sex)
{
	Sex = _sex;
	return 1; //enum не дасть ввести лєвак (я так думаю :))
}

//bool setPhoneNumber(const char* phoneNumber);
bool Person::setPhoneNumber(const char* phoneNumber)
{
	return makePhoneFromStr(phoneNumber);
}


Person::~Person()
{
	if (Fam)
		delete[] Fam;

	if(Imn)
		delete[] Imn;
	
	if(Otc)
		delete[] Otc;
	
	if(DrStr)
		delete[] DrStr;
	
	if (PhoneNumber)
		delete[] PhoneNumber;
}