#include "ConManip.h"

HANDLE hand1 = GetStdHandle(STD_OUTPUT_HANDLE);

void gtoxy(int x, int y, WORD color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand1, coord);
	SetConsoleTextAttribute(hand1, color);
}

void gtoxy(int x, int y, int count, WORD color)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hand1, coord);
	SetConsoleTextAttribute(hand1, color);
	for (int a(0); a < count; a++)
		std::cout << ' ';
}

void gtoxy(int x, int y, int countX, int countY, WORD color)
{
	SetConsoleTextAttribute(hand1, color);

	for (int a(0); a < countY; a++)
	{
		COORD coord = { x, y + a };
		SetConsoleCursorPosition(hand1, coord);
		for (int b(0); b < countX; b++)
			std::cout << ' ';
	}
}