#include <Windows.h>
#include "Group.h"
#include "Head.h"
#include "Menu.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu m;
	m.addPunkt(0, "1. —творити нову групу (додати)");
	m.addPunkt(0, "2. ¬идалити групу");
	m.addPunkt(0, "3. ¬ибрати групу (дл€ роботи з нею)");
	m.addPunkt(0, "4. –обота з групою (спочатку п.3) >>>");
	m.addMenu(4);
	m.addPunkt(4, "1. ѕерегл€д групи");
	m.addPunkt(4, "2. ƒодати студента");
	m.addPunkt(4, "3. ¬идалити студента");
	m.addPunkt(4, "4. ѕеревести студента в ≥ншу групу");
	m.addPunkt(4, "5. “ест менюшки >>>");
	m.addMenu(45);
	m.addPunkt(45, "1. ще €кийсь пункт");
	m.addPunkt(45, "2. ≥ ще один >>>");
	m.addMenu(452);
	m.addPunkt(452, "1. довга ф≥гн€€€€€€€€€€€€€€€");
	m.addPunkt(452, "2. коротша");

	Groups groups = { nullptr, 0, -1 };
	int res = 0;

	do{
		res = m.runMenu();
		menuResultCatch(res, groups);
	} while (res);
	
	gotoxy(0, 10, 7 | 0 << 4);
	return 0;
}

