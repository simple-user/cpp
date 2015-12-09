#include <iostream>
#include <Windows.h>
#include "Header.h"

using namespace std;

int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Fortress f(4, 4);

	while (f.shoot());

	return 0;

}

