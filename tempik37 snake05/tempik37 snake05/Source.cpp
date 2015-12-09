#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include "Pole.h"
#include "Nyamka.h"
#include "Snake.h"
#include "Menu.h"

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
	
	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	Pole p(1, 1, 70, 20);
	Nyamka n(p);
	Snake s(3, p,n);
	Menu m(n,p,s);

	
	m.runStartMenu();
	return 0;

	p.drawPole();
	
	int resGame = 0;
	if (resGame=s.move())
	{
		COORD co = { 0, p.yMax + 2 };
		SetConsoleCursorPosition(h, co);
		if (resGame == 1)
			cout << "You win!             ";
		else
			cout << "You lose!              ";
	}
	
	int arrKey[2] = {};
	do
	{
		arrKey[0] = _getch();
		if (_kbhit()) arrKey[1] = _getch();
	} while (arrKey[0] != 27);


	


	_EXEPT_END
	return 0;
}



