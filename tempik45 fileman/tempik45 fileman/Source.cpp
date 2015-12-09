#include <iostream>
#include <Windows.h>
#include "side.h"
#include <string>

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


	//for (unsigned int a = 0; a < 300; ++a)
	//	cout << a << " - " << (signed char)a << " - " << (unsigned char)a << endl;
	//return 0;

	side left("c:\\", 0, 3);
	side right("d:\\", 40, 3);
	
	left.show();
	right.show();
	
	/*
	string buf;
	left.makeLine(left.files[0], buf);
	cout << buf << endl;
	*/

	/* CopyFileA("opa1.txt", "opa2.txt", 0);
	MoveFileA("opa2.txt", "opa3.txt");
	*/

	_EXEPT_END
	return 0;
}