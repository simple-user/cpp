#include "Menu.h"

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y, WORD color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color);
}

void gotoxy(int x, int y, int count, WORD color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color);
	for (int a(0); a < count; a++)
		cout << ' ';
}

void gotoxy(int x, int y, int countX, int countY, WORD color)
{
	SetConsoleTextAttribute(hand, color);

	for (int a(0); a < countY; a++)
	{
		COORD coord = { x, y+a };
		SetConsoleCursorPosition(hand, coord);
		for (int b(0); b < countX; b++)
			cout << ' ';
	}
}


Menu::Menu(WORD actMCol, WORD actPCol, WORD inactMCol, WORD inactPCol) : activeMenuColor(actMCol), activePunctColor(actPCol), inactiveMenuColor(inactMCol), inactivePunctColor(inactPCol)
{
	Menushka m;
	// m.indexMenu = menu.size(); // індекс доданої менюшки
	m.indexParentMenu = -1;
	// m.levelMenu = 0;
	m.maxLenPunkt = 0;
	// m.nomParrentMenu = -1;
	m.addrMenuN = 0;
	m.xPos = 0;
	m.yPos = 0;
	m.activePunktIndex = 0;
	
	menu.push_back(m);
	
	activeMenushkaIndex = 0;
}


bool Menu::addPunkt(int addrMenuNum, string name)
{
	for (auto &menushka : menu)
	{
		if (menushka.addrMenuN == addrMenuNum)
		{
			PunktMenushka p;
			p.addrPunktN = addrMenuNum * 10 + menushka.arrPunkt.size() + 1; // +1 бо нумерація пунктів з 1 (бо пофігу + клієнт юзабіліті)
			p.indexChildMenu = 0;
			// p.nomMenu = menushka.arrPunkt.size() + 1;
			p.strPunkt = std::move(name);   // для швидкості головне не забути :)
			menushka.arrPunkt.push_back(p);
			
			menushka.maxLenPunkt = menushka.arrPunkt[0].strPunkt.size();
			for (auto punkt : menushka.arrPunkt) //знаходимо найдовшу назву меню
			{
				if (menushka.maxLenPunkt < punkt.strPunkt.size())
					menushka.maxLenPunkt = punkt.strPunkt.size();
			}

			if (menushka.xPos + menushka.maxLenPunkt > SCREENWIDTH) // якщо вивід менюшки не влізе
				menushka.xPos = menushka.xPos - menu[menushka.indexParentMenu].maxLenPunkt - menushka.maxLenPunkt;
				//menushka.xPos = SCREENWIDTH - menushka.maxLenPunkt;

			return 1;
		}
	}
	return 0;
}

bool Menu::addMenu(int addr)
{
	vector<int> arrAddrLocal;
	int t = 0;
	int k = 1;
	while (1)
	{
		t = (addr / k) % 10;
		k *= 10;
		if (!t)
			break;
		arrAddrLocal.insert(arrAddrLocal.cbegin(), t);
	} // цими танцами з бубном ми записали числову адресу поциферно в масив
	// тепер можна йти за адресою :)

	int parentIndex = 0;
	for (size_t a(0); a < arrAddrLocal.size() - 1; a++)
		if ((parentIndex = menu[parentIndex].arrPunkt[arrAddrLocal[a] - 1].indexChildMenu) == 0)
			return 0;

	Menushka m;
	m.activePunktIndex = 0;
	m.addrMenuN = addr;
	// m.indexMenu = menu.size();
	m.maxLenPunkt = 0;
	// m.nomParrentMenu = addr % 10;
	
	m.indexParentMenu = parentIndex;
	// m.levelMenu = parentIndex + 1;
	m.xPos = menu[parentIndex].xPos + menu[parentIndex].maxLenPunkt;
	m.yPos = menu[parentIndex].yPos + (addr % 10) - 1;
	menu.push_back(m);

	menu[parentIndex].arrPunkt[addr % 10 - 1].indexChildMenu = menu.size() - 1;
	return 1;
}

void Menu::printMenushka(bool gray, int indMenu) const
{
	WORD pColor = gray ? inactivePunctColor : activePunctColor;
	WORD mColor = gray ? inactiveMenuColor : activeMenuColor;

	if (indMenu == -1)
		indMenu = activeMenushkaIndex;
	const Menushka& menushka = menu[indMenu];
	
	for (size_t a(0); a < menushka.arrPunkt.size(); a++)
	{
		if (menushka.activePunktIndex == a)
			gotoxy(menushka.xPos, menushka.yPos + a, pColor);
		else
			gotoxy(menushka.xPos, menushka.yPos + a, mColor);
		
		cout << menushka.arrPunkt[a].strPunkt;
		for (size_t b = menushka.arrPunkt[a].strPunkt.size(); b < menushka.maxLenPunkt; b++) //добиваємо пробілами (для рівності виводу)
			cout << ' ';
		cout << endl;
	}
}

void Menu::printMenushkaBlack(int indMenu) const
{
	if (indMenu == -1)
		indMenu = activeMenushkaIndex;
	const Menushka& menushka = menu[indMenu];

	for (size_t a(0); a < menushka.arrPunkt.size(); a++)
	{
		gotoxy(menushka.xPos, menushka.yPos + a, 0); // 0 -> (0 | 0 << 4) black txt, black bg
		for (size_t b = 0; b < menushka.maxLenPunkt; b++) //забиваємо пробілами (все)
			cout << ' ';
		cout << endl;
	}
}

void Menu::goUp()
{
	if (menu[activeMenushkaIndex].activePunktIndex>0)
	{
		Menushka &menushka = menu[activeMenushkaIndex];
		gotoxy(menushka.xPos, menushka.yPos + menushka.activePunktIndex, activeMenuColor);
		cout << menushka.arrPunkt[menushka.activePunktIndex].strPunkt;
		for (size_t b = menushka.arrPunkt[menushka.activePunktIndex].strPunkt.size(); b < menushka.maxLenPunkt; b++) //добиваємо пробілами (для рівності виводу)
			cout << ' ';
		cout << endl;

		menushka.activePunktIndex--;

		gotoxy(menushka.xPos, menushka.yPos + menushka.activePunktIndex, activePunctColor);
		cout << menushka.arrPunkt[menushka.activePunktIndex].strPunkt;
		for (size_t b = menushka.arrPunkt[menushka.activePunktIndex].strPunkt.size(); b < menushka.maxLenPunkt; b++) //добиваємо пробілами (для рівності виводу)
			cout << ' ';
		cout << endl;

	}
}

void Menu::goDown()
{
	if (menu[activeMenushkaIndex].activePunktIndex < menu[activeMenushkaIndex].arrPunkt.size()-1)
	{
		Menushka &menushka = menu[activeMenushkaIndex];
		gotoxy(menushka.xPos, menushka.yPos + menushka.activePunktIndex, activeMenuColor);
		cout << menushka.arrPunkt[menushka.activePunktIndex].strPunkt;
		for (size_t b = menushka.arrPunkt[menushka.activePunktIndex].strPunkt.size(); b < menushka.maxLenPunkt; b++) //добиваємо пробілами (для рівності виводу)
			cout << ' ';
		cout << endl;

		menushka.activePunktIndex++;

		gotoxy(menushka.xPos, menushka.yPos + menushka.activePunktIndex, activePunctColor);
		cout << menushka.arrPunkt[menushka.activePunktIndex].strPunkt;
		for (size_t b = menushka.arrPunkt[menushka.activePunktIndex].strPunkt.size(); b < menushka.maxLenPunkt; b++) //добиваємо пробілами (для рівності виводу)
			cout << ' ';
		cout << endl;

	}
}

int Menu::goEnter(bool Enter)
{
	Menushka &menushka = menu[activeMenushkaIndex];
	if (!menushka.arrPunkt[menushka.activePunktIndex].indexChildMenu && Enter)
	{
		printMenushka(true);
		int tempActivePunctIndex = menushka.activePunktIndex;
		menushka.activePunktIndex = 0;
		return menushka.arrPunkt[tempActivePunctIndex].addrPunktN;
	}
	else if (!menushka.arrPunkt[menushka.activePunktIndex].indexChildMenu && !Enter)
		return 0;

	printMenushka(true); // gray
	activeMenushkaIndex = menushka.arrPunkt[menushka.activePunktIndex].indexChildMenu;
	printMenushka();
	return 0;
}

void Menu::goEsc(bool Esc)
{
	if (!activeMenushkaIndex && Esc)
	{
		printMenushkaBlack();
		activeMenushkaIndex--;
		return;
	}
	else if (!activeMenushkaIndex && !Esc)
		return;

	menu[activeMenushkaIndex].activePunktIndex = 0;
	printMenushkaBlack();
	activeMenushkaIndex = menu[activeMenushkaIndex].indexParentMenu;
	printMenushka();
}

int Menu::runMenu(int addr)
{
	activeMenushkaIndex = 0;
	char key = 0;
	int result = 0;
	printMenushka();
	do
	{
		do
		{
			key = _getch();
		} while (key!=UP && key!=DOWN && key!=ENTER && key!=ESC && key!=RIGHT && key!=LEFT);

		switch (key)
		{
		case UP: goUp(); break;
		case DOWN: goDown(); break;
		case RIGHT: goEnter(0); break;
		case ENTER: result=goEnter(); break;
		case LEFT: goEsc(0); break;
		case ESC: goEsc(); break;
		}
	} while (activeMenushkaIndex >= 0 && !result);
	return result;
}