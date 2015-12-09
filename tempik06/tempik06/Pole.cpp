#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Kletka.h"
#include "Korablik.h"
#include "Pole.h"
#include "Header.h"


using namespace std;

Pole::Pole(int x, int y, bool my) :count_ñlosed(100), count_closed_pal(20), x_move(x + 3), y_move(y + 2), isMy(my), x_at(0), y_at(0), x_happy(-1), y_happy(-1)
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
				cout << ' ';
		}
	}
}


char Pole::move_cursor()
{
	char ch=0;
	gotoxy(x_at+x_move, y_at+y_move);

	do
	{
		ch = _getch();
		switch (ch)
		{
		case UP: if (y_at > 0) y_at--; break;
		case DOWN: if (y_at < 9) y_at++; break;
		case LEFT: if (x_at > 0) x_at--; break;
		case RIGHT: if (x_at < 9) x_at++; break;
		}
		gotoxy(x_at + x_move, y_at + y_move);
	} while (ch != ENTER && ch!=SPACE && ch!=ESC);

	return ch;
}


/*
bool Pole::move(vector<Korablik> &korabli)
{
	if (isMy)
		return move_my(korabli);
	else
		return move_comp(korabli);

}

bool Pole::move_comp(vector<Korablik> &korabli)
{
	srand(unsigned(time(0)));
	int rnd_x = 0;
	int rnd_y = 0;

	rnd_x = rand() % 10;
	rnd_y = rand() % 10;


}
*/