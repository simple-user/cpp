#include <iostream>
#include <Windows.h>
#include "Account.h"
#include "Person.h"

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
	//// move constructor
	//Person p4(std::move(p1));
	//cout << "P4------------------------------------------\n";
	//cout << p4 << endl;

	//// move operator=
	//// p4 = Person("Табурєткін", "Іван2", "Іванович2", "22.02.1922", MALE, "222");
	//cout << "P4------------------------------------------\n";
	//cout << p4 << endl;





	return 0;

	

}