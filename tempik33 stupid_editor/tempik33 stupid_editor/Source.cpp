#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include "MyFrame.h"


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
using std::string;

int main()
{

	_EXEPT_START
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	

/*
      tii 
   this is new linre


*/

	MyFrame f;
	f.keyPress();
	
	gotoxy(0, 24, 7);
	_EXEPT_END
	return 0;
}







