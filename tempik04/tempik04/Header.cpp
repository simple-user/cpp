#include <Windows.h>
#include <iostream>
#include <string>
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


