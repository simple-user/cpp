#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "Inversion.h"
#include <vector>
#include <algorithm>
#include <functional>


//using std::cout;
//using std::endl;
//using std::string;
//using std::vector;

using namespace std;

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

	Inversion in("invertDic.txt");
	in.push("мама");
	in.push("тато");

	for (auto &a : in)
		cout << a << endl;
	
	_EXEPT_END
	return 0;
}