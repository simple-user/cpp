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

void gotoxy(int x, int y, int colort, int colorb,  char ch)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand, coord);
	SetConsoleTextAttribute(hand, colort | colorb << 4);
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
		pole.x_at = ch - 'a';
		pole.y_at = n - 1;
		
		if (pole.x_at<0 || pole.x_at>9 || pole.y_at<0 || pole.y_at>9)
		{
			gotoxy(0, 17, 79, 17, 7, ' ');
			cin.clear();
			while (cin.get() != '\n');
			gotoxy(0, 17, 7, "MIMO!!!! Vvodi she raz: ");
		}
		else if (pole.arr_k[pole.x_at][pole.y_at].opened)
		{
			gotoxy(0, 17, 79, 17, 7, ' ');
			gotoxy(0, 17, 12, "WRONG CELL!!!! she raz: ");
		}
		else
		{
			move_done = move_maker(korabli, pole, turn);
			gotoxy(0, 17, 79, 17, 7, ' ');
			if (!move_done)
			{
				gotoxy(0, 17, 7, "Good one!!!! Have one more sproba!!! :))) :");
			}
		}
	}
	return 0;
}

void operator>>(istream &is, Buttons &b)
{
	int t;
	is >> t;
	b = Buttons(t);
}

bool move_my2(vector<Korablik> &korabli, Pole & pole, int &turn)
{
	char ch = 0;
	int n = 0;
	bool move_done = 0;

	gotoxy(0, 17, 79, 17, 7, ' ');
	gotoxy(0, 17, 7, "Ходить юзер. Стрілочками переміщай курсорчик. Ентер, спробіл - вистрілити");
	while (!move_done)
	{
		if (pole.move_cursor()==ESC)
			return 1;
		

		if (pole.arr_k[pole.x_at][pole.y_at].opened)
		{
			gotoxy(0, 17, 79, 17, 7, ' ');
			gotoxy(0, 17, 12, "Клітинка вже відмічена. Ходи ще раз.");
		}
		else
		{
			move_done = move_maker(korabli, pole, turn);
			if (!move_done)
			{
				gotoxy(0, 17, 79, 17, 7, ' ');
				gotoxy(0, 17, 7, "Хороше попадання. Ходи ще раз.");
			}

		}
		gotoxy(pole.x_move - 3, 15, pole.x_move + 19 - 3, 15, 7, ' ');
		gotoxy(pole.x_move - 3, 15), cout << "Залишилось палуб: " << pole.count_closed_pal << "  ";

	}

	gotoxy(0, 17, 79, 17, 7, ' '); //кінець ходу почистились

	if (pole.count_closed_pal <= 0)
		return 1;

	return 0;
}

bool move_maker(vector<Korablik> &korabli, Pole &pole, int &turn)
{
	bool move_done = 0;
	bool finded = 0;
	int x = pole.x_at, y = pole.y_at;

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
					p.killed_paluba = 1;
					k.count_pal_alive--; // -1 палуба на кораблі
					pole.count_closed_pal--; // -1 палуба на всьому полі (на початку гри =20) 
					finded = 1; // для виходу з усіх циклів
					
					if (k.count_pal_alive < 0) // тестік (не повинно бути)
						cout << "ALERT!!! WE HAVE NO FREE PALUB FOR DEL (now below zero!!!1)!!!!";
					else if (k.count_pal_alive == 0) //killed ship!!!
					{
						killed_ship(k, pole);
						if (pole.count_closed_pal <= 0)
						{
							gotoxy(0, 20, 79, 20, 7, ' ');
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
	//gotoxy(pole.x_move, 19, 7, "Comp finished his turn!");
	Sleep(300);
	
	return move_done;
}
bool find_free_around_happy(Pole &pole)
{
	int xtemp = 0, ytemp = 0;
	for (int xi = (pole.x_happy == 0 ? 0 : pole.x_happy - 1); xi <= pole.x_happy + 1 && xi < 10; xi++)
	{
		for (int yi = (pole.y_happy == 0 ? 0 : pole.y_happy - 1); yi <= pole.y_happy + 1 && yi < 10; yi++)
		{
			if (abs(xi - pole.x_happy) == abs(yi - pole.y_happy))
				continue;
			if (pole.arr_k[xi][yi].opened && pole.arr_k[xi][yi].isPaluba)
			{
				// тобто ми пройшли довкола і знайшли поряд відкриту палубу
				if (xi == pole.x_happy) // лінія вертикальна
				{
					// ідемо вверх
					xtemp = xi;
					ytemp = yi;
					while (ytemp > 0 && pole.arr_k[xtemp][ytemp].opened == 1 && pole.arr_k[xtemp][ytemp].isPaluba == 1)
					{
						ytemp--;
					} 
					if (pole.arr_k[xtemp][ytemp].opened != 1)
					{	
						pole.x_at = xtemp;
						pole.y_at = ytemp;
						return 1;
					}

					// ідемо вниз
					xtemp = xi;
					ytemp = yi;
					while (ytemp < 9 && pole.arr_k[xtemp][ytemp].opened == 1 && pole.arr_k[xtemp][ytemp].isPaluba == 1)
					{
						ytemp++;
					} 
					if (pole.arr_k[xtemp][ytemp].opened != 1)
					{
						pole.x_at = xtemp;
						pole.y_at = ytemp;
						return 1;
					}
				}
				else // лінія горизонтальна
				{
					// ідемо вліво
					xtemp = xi;
					ytemp = yi;
					while (xtemp > 0 && pole.arr_k[xtemp][ytemp].opened == 1 && pole.arr_k[xtemp][ytemp].isPaluba == 1)
					{
						xtemp--;
					} 
					if (pole.arr_k[xtemp][ytemp].opened != 1)
					{
						pole.x_at = xtemp;
						pole.y_at = ytemp;
						return 1;
					}

					// ідемо вправо
					xtemp = xi;
					ytemp = yi;
					while (xtemp < 9 && pole.arr_k[xtemp][ytemp].opened == 1 && pole.arr_k[xtemp][ytemp].isPaluba == 1)
					{
						xtemp++;
					} 
					if (pole.arr_k[xtemp][ytemp].opened != 1)
					{
						pole.x_at = xtemp;
						pole.y_at = ytemp;
						return 1;
					}
				}

				//якщо сюди дійшли то або ми лохі або корабль вже повністю відкрито а значення хеппі лишилось				
				// або промто поряд немає відкритої палуби :))
				/*pole.x_happy = -1;
				pole.y_happy = -1;
				return 0;*/
			}
		}
	}


	for (int xi = (pole.x_happy == 0 ? 0 : pole.x_happy - 1); xi <= pole.x_happy + 1 && xi < 10; xi++)
	{
		for (int yi = (pole.y_happy == 0 ? 0 : pole.y_happy - 1); yi <= pole.y_happy + 1 && yi < 10; yi++)
		{
			if (abs(xi - pole.x_happy) == abs(yi - pole.y_happy))
				continue;
			if (!pole.arr_k[xi][yi].opened)
			{
				pole.x_at = xi;
				pole.y_at = yi;
				return 1;
			}
		}
	}

	pole.x_happy = -1;
	pole.y_happy = -1;
	return 0;
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

		gotoxy(0, 17, 7, "Ходить компік.");
		Sleep(500);
		if (pole.x_happy==-1 || !find_free_around_happy(pole))
		{
			do
			{
				rnd_x = rand() % 10;
				rnd_y = rand() % 10;
			} while (pole.arr_k[rnd_x][rnd_y].opened);
			pole.x_at = rnd_x;
			pole.y_at = rnd_y;
		}
		
		move_done = move_maker(korabli, pole, turn);
		if (!move_done)
		{
			gotoxy(0, 17, 7, "Ходить компік. Молодчина! Попав. Ходить ще раз.");
			pole.x_happy = pole.x_at;
			pole.y_happy = pole.y_at;
		}

		gotoxy(pole.x_move - 3, 15, pole.x_move + 19 - 3, 15, 7, ' ');
		gotoxy(pole.x_move - 3, 15), cout << "Залишилось палуб: " << pole.count_closed_pal << "  ";

	}
	
	gotoxy(0, 17, 79, 17, 7, ' '); //кінець ходу почистились
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
