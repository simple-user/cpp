#include <cmath>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Odometr.h"
#include "Menu.h"
#include "lib.h"
using namespace std;

int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu m1;
	Odometr *od = nullptr;
	int res = 0;

	m1.addPunkt(0, "1. Ініціалізувати параметри");
	m1.addPunkt(0, "2. Проїхати 1 км");
	m1.addPunkt(0, "3. Проїхати Х км");
	m1.addPunkt(0, "4. Залити 1 літр до бензобаку");
	m1.addPunkt(0, "5. Залити Х літрів до бензобаку");
	m1.addPunkt(0, "6. Вивести інфу по датчиках");

	
	do
	{
		res = m1.runMenu();
		switch (res)
		{
		case 1:	odInit(od); break;
		case 2:	goOneKm(od); break;
		case 3:	goXKm(od); break;
		case 4:	putOneLiter(od); break;
		case 5:	putXLiters(od); break;
		case 6:	
			printInfa(od);
			system("pause");
			system("cls"); 
			break;
		}
	} while (res);

	delete od;

	return 0;

}

