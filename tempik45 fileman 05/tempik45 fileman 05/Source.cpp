#include <iostream>
#include <Windows.h>
#include "side.h"
#include "fileMan.h"
#include <string>
#include <conio.h>

using std::cout;
using std::endl;
using std::string;


#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) \
{ \
	std::cout << "Error: " << e.what(); \
} \
	catch (string &s) \
{\
	std::cout << s; \
}\
catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
}



int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//while (1)
	//	cout << _getch() << '\n';

	fileMan f("z:\\", "z:\\", 0, 3);
	f.keyLisener();

	_EXEPT_END

	SetConsoleCursorPosition(side::hand, { 0, 24 });
	SetConsoleTextAttribute(side::hand, 7);
	_getch();
	return 0;
}