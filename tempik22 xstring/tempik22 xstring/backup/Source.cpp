#include <Windows.h>
#include "Xstring.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Xstring s1(Xstring("Hello"));
	Xstring s2("world!");

	
	std::cout << s1 + " " + s2 << std::endl;
	std::cout << s1*s2 << std::endl;
	std::cout << s1*"world!" << std::endl;
	std::cout << "hello"*s2 << std::endl;

	return 0;
}

