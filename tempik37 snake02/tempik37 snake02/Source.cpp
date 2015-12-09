#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>
#include <conio.h>
#include "Pole.h"
#include "Nyamka.h"
#include "Snake.h"

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
	Nyamka n(3, p);
	Snake s(3, 500, p);

	p.drawPole();

	while (1)
	{
		s.step();
		Sleep(100);
	}


	/*for (int y = p.yMin; y <= p.yMax; ++y)
	for (int x = p.xMin; x <= p.xMax; ++x)
	{
		COORD c = { x, y };
		if (n.checkNyam(c))
			Sleep(700);
		Sleep(10);
		SetConsoleCursorPosition(h, c);
		cout << ".";
		p.setCoord(x, y, 1);

	}
*/


	_EXEPT_END
	return 0;
}



