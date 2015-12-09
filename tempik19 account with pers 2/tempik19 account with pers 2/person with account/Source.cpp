#include <iostream>
#include <Windows.h>
#include "Account.h"
#include "Person.h"
#define L cout<<"_______________________________________________\n";

using std::cout;
using std::endl;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// c-tor by default with arguments
	Person p1("Пупкін", "Іван", "Іванович", "12.04.1986", MALE, "+380971234567", Account("0000001", "UAH", 10000));
	cout << "P1------------------------------------------\n";
	p1.Print();
	p1.accountData()->addMoney("UAH", 10000);
	L
	p1.Print();
	L
	// move constructor
	Person p4(std::move(p1));
	cout << "P4------------------------------------------\n";
	cout << p4 << endl;


	return 0;

	

}