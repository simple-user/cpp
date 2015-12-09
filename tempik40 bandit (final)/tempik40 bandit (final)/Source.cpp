#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "Drum.h"
#include "Bandit.h"

using std::cout;
using std::endl;

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
	srand(unsigned(time(0)));

	
	Bandit b(4, 4, 100, 1500);

	b.show();
	
	if (!b.game())
	{
		SetConsoleCursorPosition(Drum::hand, COORD{ 0, 20 });
		cout << "Bye looser :)\n";
	}
	_EXEPT_END
	return 0;
}
