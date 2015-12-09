#include <iostream>
#include <ctime>
#include <string>
#include "Korablik.h"
#include "Pole.h"
#include "Header.h"

using namespace std;

Korablik::Korablik(int p, Pole &_pole, bool auto_creation) :count_pal(p), killed(0), pole(_pole)
{
	if (auto_creation)
		auto_create();
	else
		manual_create();
}

Korablik::~Korablik()
{}

void Korablik::about_me()
{
	cout << "Korabik of " << count_pal << " palub:\n";
	cout << "Killed: " << killed << endl;
	cout << "Palubi:\n";
	for (auto a : palubi)
	{
		cout << "isPal: " << a.isPal << ", xpal: " << a.x_pal << ", y_pal: " << a.y_pal << endl;
	}
	cout << "------end------\n\n";
}

void Korablik::manual_create()
{
	char ch = 0;
	int n = 0;
	gotoxy(0, 15, 7);
	
	cout << "Information about ship of " << count_pal << " decks.               " << endl;

	Paluba pal;

	for (int a(0); a < count_pal; a++)
	{
		gotoxy(0, 16, 7);
		cout << "Deck number " << a + 1 << endl;

		cout << "Input a-j: ", cin >> ch, pal.x_pal = ch - 'a';
		cout << "Input 1-10: ", cin >> n, pal.y_pal = n - 1;
		gotoxy(0, 15, 40, 18, 7, ' ');
		pal.isPal = 1;
		palubi.push_back(pal);
		pole.arr_k[pal.x_pal][pal.y_pal].isPaluba = 1;
		gotoxy(pole.x_move + pal.x_pal, pole.y_move + pal.y_pal, 7), cout << '0';

	}
}

void Korablik::auto_create()
{
	bool horisontal = 0; // 1-horisontal 0-vertical
	int up_left = 0; //  -1: up (or left) 1: down (or right)
	int first_x = 0;
	int first_y = 0;
	srand(unsigned(time(0)));
	
	Paluba pal;

	bool contin = 0;
	while (1)
	{
		horisontal = rand() % 2;
		up_left= (up_left = rand() % 2) + up_left - 1; // 0=>-1 , 1=>1
		
		first_x = rand() % 10;
		first_y = rand() % 10;
		contin = 0;

		if (horisontal)
		{
			for (int a(0); a < count_pal; a++)
			{
				if (!is_good_place(first_x + a*up_left, first_y))
				{
					contin = 1;
					break;
				}
					
			}
		}
		else
		{
			for (int a(0); a < count_pal; a++)
			{
				if (!is_good_place(first_x, first_y + a*up_left))
				{
					contin = 1;
					break;
				}
			}
		}
		
		if (contin)
			continue;

		// якщо усі перевірки пройдені - вписуємо

		if (horisontal)
		{
			for (int a(0); a < count_pal; a++)
			{
				pole.arr_k[first_x + a*up_left][first_y].isPaluba = 1;
				pal.isPal = 1;
				pal.x_pal = first_x + a*up_left;
				pal.y_pal = first_y;
				palubi.push_back(pal);
			}
		}
		else
		{
			for (int a(0); a < count_pal; a++)
			{
				pole.arr_k[first_x][first_y + a*up_left].isPaluba = 1;
				pal.isPal = 1;
				pal.x_pal = first_x;
				pal.y_pal = first_y + a*up_left;
				palubi.push_back(pal);
			}
		}

		break;
	}
}

bool Korablik::is_good_place(int x, int y)
{
	
	if (x<0 || x>9 || y<0 || y>9)
		return 0;

	if (pole.arr_k[x][y].isPaluba)
		return 0;

	for (int xi = (x == 0 ? 0 : x - 1); xi <= x + 1 && xi < 10; xi++)
	{
		for (int yi = (y == 0 ? 0 : y - 1); yi <= y + 1 && yi < 10; yi++)
		{
			if (pole.arr_k[xi][yi].isPaluba)
				return 0;
		}
	}

	return 1;
}