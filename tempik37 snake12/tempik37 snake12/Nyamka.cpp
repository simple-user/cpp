#include "Nyamka.h"


Nyamka::Nyamka(Pole &p) : pole(&p), gamePoints(0)
{	
}

void Nyamka::init()
{
	srand(unsigned(time(0)));
	gamePoints = 0;

	for (size_t c = countNyam; c; --c)
	{
		size_t x = 0;
		size_t y = 0;
		if (!pole->isFree())
			throw exception(string("Error while constract nyamka. No free places!").c_str());

		do
		{
			x = rand() % pole->width;
			y = rand() % pole->height;
		} while (pole->chekCoord(x, y)); // крутиться поки вертає занято


		vecNyam.emplace_back(x, y, getColorNyam()); // оп-па! :)
		pole->setCoord(x, y, true, vecNyam[vecNyam.size()-1].color, CharNyamka);

	}

	showStartNyamki();
	writePoints(7);
}

void Nyamka::createNewNyam(vector<Nyam>::iterator &itNyam)
{
	if (!pole->isFree())
	{
		vecNyam.erase(itNyam);
		return; //якщо вже немає пустих клітинок то видаляємо!
	}
	
	size_t x = 0;
	size_t y = 0;

	do
	{
		x = rand() % pole->width;
		y = rand() % pole->height;
	} while (pole->chekCoord(x, y)); // крутиться поки вертає занято


	 // оп-па! :)
	itNyam->coord.X = x;
	itNyam->coord.Y = y;
	itNyam->color = getColorNyam();

	pole->setCoord(x, y, true, itNyam->color, CharNyamka);

	showOneNyam(*itNyam);
}

void Nyamka::showStartNyamki() const
{
	for (auto a : vecNyam)
	{
		showOneNyam(a);
	}
}

inline void Nyamka::showOneNyam(Nyam n) const
{
	n.coord.X += pole->xMin;
	n.coord.Y += pole->yMin;
	SetConsoleCursorPosition(pole->hand, n.coord);
	SetConsoleTextAttribute(pole->hand, n.color);
	cout << CharNyamka;
}

bool Nyamka::checkNyam(COORD c, WORD & col)
{
	bool res = false;
	for (vector<Nyam>::iterator it = vecNyam.begin(); it!=vecNyam.end(); ++it)
	{
		if (it->coord == c)
		{
			col = it->color;
			switch (it->color)
			{
			case BLUE: ++gamePoints; break;
			case GREEN: gamePoints+=2; break;
			case RED: gamePoints+=3; break;
			case WHITE: gamePoints+=4; break;
			}
			
			
			writePoints(col);

			createNewNyam(it);
			res = true;
			break;
		}
	}
	return res;
}