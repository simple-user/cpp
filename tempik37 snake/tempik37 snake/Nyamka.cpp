#include "Nyamka.h"


Nyamka::Nyamka(size_t cN, Pole &p) : pole(p)
{
	srand(unsigned(time(0)));
	for (size_t c = cN; c; --c)
	{
		size_t x = 0;
		size_t y = 0;
		if (!p.isFree())
			throw exception(string("Error while constract nyamka. No free places!").c_str());

		do
		{
			x = p.xMin + rand() % p.width;
			y = p.yMin + rand() % p.height;
		} while (p.chekCoord(x, y)); // крутиться поки вертає занято

		
		p.setCoord(x, y, 1);
		vecNyam.emplace_back(x, y, 7); // оп-па! :)

	}

	showStartNyamki();
}

void Nyamka::showStartNyamki() const
{
	for (auto a : vecNyam)
	{
		SetConsoleCursorPosition(pole.hand, a.coord);
		SetConsoleTextAttribute(pole.hand, a.color);
		cout << CharNyamka;
	}
}

bool Nyamka::checkNyam(COORD c)
{
	for (auto &a : vecNyam)
	{
		if (a.coord == c)
		{

		}
	}
}