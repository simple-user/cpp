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

// enum Buttons { UP = 72, DOWN = 80, ESC = 27, ENTER = 13, SKIP = 224 };

int main() 
{
	_EXEPT_START

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//while (1)
	//	cout << _getch() << '\n';

	fileMan f("z:\\", "z:\\", 0, 3);
	f.keyLisener();

	//for (unsigned int a = 0; a < 300; ++a)
	//	cout << a << " - " << (signed char)a << " - " << (unsigned char)a << endl;
	//return 0;

	/*side left("d:\\", 0, 3);
	side right("Z:\\", 40, 3);
	char key =  0 ;


	left.show();
	right.show();
	while (key != 27)
	{
		key = _getch();
		switch (key)
		{
		case UP:
			left.mooveUp();
			break;
		case DOWN:
			left.mooveDown();
			break;
		case ENTER:
			left.enter();
			break;
		case 'w':
			right.mooveUp();
			break;
		case 's':
			right.mooveDown();
			break;
		}
	}

	left.inactive();
	_getch();
	left.active();
	right.inactive();
	*/
	/*
	string buf;
	left.makeLine(left.files[0], buf);
	cout << buf << endl;
	*/

	/* CopyFileA("opa1.txt", "opa2.txt", 0);
	MoveFileA("opa2.txt", "opa3.txt");
	*/


	_EXEPT_END

	SetConsoleCursorPosition(side::hand, { 0, 24 });
	SetConsoleTextAttribute(side::hand, 7);
	_getch();
	return 0;
}