#include "Pole.h"

bool operator==(COORD a, COORD b)
{
	if (a.X == b.X && a.Y == b.Y)
		return 1;
	return 0;
}


Pole::Pole(size_t x, size_t y, size_t w, size_t h) : xPos(x), yPos(y), width(w), height(h),
	xMin(x), yMin(y), xMax(w + x - 1), yMax(h + y - 1), leftFree(w*h),
	hand(GetStdHandle(STD_OUTPUT_HANDLE))
{
	if (xMax > XMAX || yMax > YMAX)
		throw exception(string("xMax or yMax error!").c_str());
	if (xMin<1 || xMin>xMax || yMin<1 || yMin>yMax)
		throw exception(string("XMin or yMin error!").c_str());

	// створюємо двухмірний масив на основі векторів :) 
	// ну не вручну ж пам"ять виділяти :)
	vecPole.resize(width);
	for (auto &a : vecPole)
	{
		a.resize(height);
		for (auto &b : a)
			b = false;   // обнулимо про всяк випадок поля
	}
}

void Pole::drawPole() const
{
	for (size_t x = xMin - 1; x <= xMax + 1; ++x)
	for (size_t y = yMin - 1; y <= yMax + 1; ++y)
	if (x == xMin - 1 || x == xMax + 1 || y == yMin - 1 || y == yMax + 1)
	{
		coord = { x, y };
		SetConsoleCursorPosition(hand, coord);
		cout << borderChar;
	}
}

bool Pole::chekCoord(size_t x, size_t y) const
{
	if (vecPole[x][y])
		return 1;
	else
		return 0;
}

void Pole::setCoord(size_t x, size_t y, bool b) 
{
	if (vecPole[x][y] == b)
		return;

	if (b)
		--leftFree;
	else
		++leftFree;
	vecPole[x][y] = b;

	/* if (!leftFree)
		return 1;
	return 0;
	*/
}

bool Pole::isFree() const
{
	if (leftFree)
		return 1;
	else
		return 0;
}