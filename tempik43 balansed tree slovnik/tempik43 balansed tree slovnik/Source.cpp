#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "dictionary.h"

using std::cout;
using std::endl;
using std::string;

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
} \
catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
}



int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	
	cout << "Welcome to doctionary!";
	dictionary d("dic.txt");
	d.addWord("2", "02");

	string *t = d.translate("1");
	if (t)
		cout << "1 - " << *t << endl;


	_EXEPT_END
	return 0;
}
