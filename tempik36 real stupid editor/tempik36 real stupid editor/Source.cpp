#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include "Menu.h"
#include "StupidEditor.h"

#define br cout << endl

#define _EXEPT_START try {
#define _EXEPT_END } \
	catch (std::exception &e) { \
	std::cout << "Error: " << e.what(); \
	} \
	catch (...) { \
	std::cout << "Что-то пошло не так... Chrome.(c) "; \
	} 

using std::cout;
using std::endl;

int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	StupidEditor se;
	se.runMenu();
	
	_EXEPT_END
	return 0;
}



