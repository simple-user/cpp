#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include "Drum.h"

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

	Drum **pDrum = new Drum*[3];

	pDrum[0] = new Drum(5, 4, 4, 3, 5, 50, 1500);
	Sleep(500);
	pDrum[1] = new Drum(5, 6, 4, 3, 8, 50, 1500);
	Sleep(500);
	pDrum[2] = new Drum(5, 8, 4, 3, 10, 50, 1500);
	
	
	
	
	_getch();

	
	do
	{
		for (size_t a = 0; a < 3; ++a)
			pDrum[a]->update();
	} while (pDrum[0]->getPeriod() < 1500 || pDrum[1]->getPeriod() < 1500 || pDrum[2]->getPeriod() < 1500);



	/*for (int a = -200; a <= 200; ++a)
	{
	cout << a << " - " << char(a) << endl;
	}*/

	SetConsoleCursorPosition(Drum::hand, COORD{ 0, 20 });
	_EXEPT_END
	return 0;
}
