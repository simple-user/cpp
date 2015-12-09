#include <iostream>
#include <string>
#include "Kletka.h"
#include "Pole.h"
#include "Header.h"

using namespace std;

Pole::Pole(int x, int y, bool my) :COUNT_K(100), COUNT_K_PAL(20), count_k_op(0), count_k_pal_op(0), x_move(x + 3), y_move(y + 2), isMy(my)
{
	for (auto &a : arr_k)
	{
		for (auto &b : a)
		{
			b.opened = 0;
			b.isPaluba = 0;
		}
	}

}

void Pole::first_draw()
{
	char ch = 0;
	for (int x(-3); x <= 10; x++)
	{
		for (int y(-2); y <= 10; y++)
		{
			if (x == -3 && y == 9)
				ch = '1';
			else if (x == -2 && (y >= 0 && y < 9))
				ch = 49 + y;
			else if (x == -2 && y == 9)
				ch = '0';
			else if ((x == -1 || x == 10) && y >= -1 && y <= 10)
				ch = '#';
			else if (y == -2 && x >= 0 && x < 10)
				ch = 'a' + x;
			else if ((y == -1 || y == 10) && x >= -1 && x <= 10)
				ch = '#';
			else
				ch = ' ';
			gotoxy(x_move + x, y_move + y, 7, ch);
		}
	}

}

void Pole::show_action()
{
	for (int x(0); x < 10; x++)
	{
		for (int y(0); y < 10; y++)
		{
			gotoxy(x + x_move, y + y_move);
			if (arr_k[x][y].isPaluba)
				cout << '0';
			else if (arr_k[x][y].promah)
				cout << '*';
			else
				cout << '-';
		}
	}
}
