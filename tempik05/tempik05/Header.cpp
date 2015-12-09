#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include "Header.h"


using namespace std;

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);


void gotoxy(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
}


void gotoxy(int x, int y, int color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color | 0 << 4);
}

void gotoxy(int x, int y, int color, char ch)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color | 0 << 4);
	cout << ch;
}

void gotoxy(int x1, int y1, int x2, int y2, int color, char ch)
{
	COORD coord;
	SetConsoleTextAttribute(hand, color | 0 << 4);
	for (int x(x1); x <= x2; x++)
	{
		for (int y(y1); y <= y2; y++)
		{
			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(hand, coord);
			cout << ch;
		}
	}

}

void gotoxy(int x, int y, int color, string str)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, color | 0 << 4);
	cout << str;
}

bool move_my(vector<Korablik> &korabli, Pole & pole, int &turn)
{
	char ch = 0;
	int n = 0;
	int x = 0, y = 0;
	bool move_done = 0;
	
	gotoxy(0, 17, 79, 17, 7, ' ');
	gotoxy(0, 17, 7, "Input cell (a1,c5, etc...)");
	while (!move_done)
	{
		cin >> ch >> n;
		x = ch - 'a';
		y = n - 1;
		
		if (x<0 || x>9 || y<0 || y>9)
		{
			gotoxy(0, 17, 79, 17, 7, ' ');
			cin.clear();
			while (cin.get() != '\n');
			gotoxy(0, 17, 7, "MIMO!!!! Vvodi she raz: ");
		}
		else if (pole.arr_k[x][y].opened)
		{
			gotoxy(0, 17, 79, 17, 7, ' ');
			gotoxy(0, 17, 12, "WRONG CELL!!!! she raz: ");
		}
		else
		{
			move_done = move_maker(korabli, pole, turn, x, y);
			gotoxy(0, 17, 79, 17, 7, ' ');
			if (!move_done)
			{
				gotoxy(0, 17, 7, "Good one!!!! Have one more sproba!!! :))) :");
			}

		}

	}

	
	
	
	return 0;
}

bool move_maker(vector<Korablik> &korabli, Pole &pole, int &turn, int x, int y)
{
	bool move_done = 0;
	bool finded = 0;
	
	pole.arr_k[x][y].opened = 1;
	move_done = 1;
	if (pole.arr_k[x][y].isPaluba)
	{
		gotoxy(x + pole.x_move, y + pole.y_move, 12, 'X');

		for (auto &k : korabli)
		{
			for (auto &p : k.palubi)
			{
				if (p.x_pal == x && p.y_pal == y && p.killed_paluba == 0)
				{
					move_done = 0; // можна ще раз походити якщо знайшов
					//turn = turn*(-1) + 1; // 0 * -1 + 1 => 1 // 1 * -1 + 1 => 0
					p.killed_paluba = 1;
					k.count_pal_alive--; // -1 палуба на кораблі
					pole.count_closed_pal--; // -1 палуба на всьому полі (на початку гри =20) 
					finded = 1; // для виходу з усіх циклів
					gotoxy(pole.x_move, 18, 7, "   ");
					cout << pole.count_closed_pal << "  ";
					if (k.count_pal_alive < 0) // тестік (не повинно бути)
						cout << "ALERT!!! WE HAVE NO FREE PALUB FOR DEL (now below zero!!!1)!!!!";
					else if (k.count_pal_alive == 0) //killed ship!!!
					{
						killed_ship(k, pole);
						if (pole.count_closed_pal <= 0)
						{
							gotoxy(0, 20, 12, "Game over :)");
							return 1;
						}

					}
					break;
				}
			}
			if (finded)
				break;
		}
	}
	else // !pole.arr_k[rnd_x][rnd_y].isPaluba
	{
		pole.arr_k[x][y].promah = 1;
		gotoxy(x + pole.x_move, y + pole.y_move, 9, '*');
	}
	gotoxy(pole.x_move, 19, 7, "Comp finished his turn!");
	Sleep(100);
	
	return move_done;
}

bool move_comp(vector<Korablik> &korabli, Pole &pole, int &turn)
{
	srand(unsigned(time(0)));
	int rnd_x = 0;
	int rnd_y = 0;
	bool finded = 0;
	bool move_done = 0;
	
	while (!move_done)
	{
		rnd_x = rand() % 10;
		rnd_y = rand() % 10;
		if (!pole.arr_k[rnd_x][rnd_y].opened)
			move_done = move_maker(korabli, pole, turn, rnd_x, rnd_y);
	}
	if (pole.count_closed_pal <= 0)
		return 1;
	else
		return 0;
}

void killed_ship(Korablik & korablik, Pole &pole)
{
	int x = 0, y = 0;
	for (auto a : korablik.palubi)
	{
		x = a.x_pal;
		y = a.y_pal;

		for (int xi = (x == 0 ? 0 : x - 1); xi <= x + 1 && xi < 10; xi++)
		{
			for (int yi = (y == 0 ? 0 : y - 1); yi <= y + 1 && yi < 10; yi++)
			{
				if (!pole.arr_k[xi][yi].opened && !pole.arr_k[xi][yi].isPaluba)
				{
					pole.arr_k[xi][yi].opened = 1;
					pole.arr_k[xi][yi].promah = 1;
					gotoxy(xi + pole.x_move, yi + pole.y_move, 9, '*');
				}
			}
		}
	}
}
