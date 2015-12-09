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
			x = rand() % p.width;
			y = rand() % p.height;
		} while (p.chekCoord(x, y)); // ��������� ���� ����� ������

		
		p.setCoord(x, y, 1);
		vecNyam.emplace_back(x, y, 7); // ��-��! :)

	}

	showStartNyamki();
}

void Nyamka::createNewNyam(vector<Nyam>::iterator &itNyam)
{
	if (!pole.isFree())
	{
		vecNyam.erase(itNyam);
		return; //���� ��� ���� ������ ������� �� ���������!
	}
	
	size_t x = 0;
	size_t y = 0;

	do
	{
		x = rand() % pole.width;
		y = rand() % pole.height;
	} while (pole.chekCoord(x, y)); // ��������� ���� ����� ������


	pole.setCoord(x, y, 1);
	 // ��-��! :)
	itNyam->coord.X = x;
	itNyam->coord.Y = y;
	itNyam->color = 7;

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
	n.coord.X += pole.xMin;
	n.coord.Y += pole.yMin;
	SetConsoleCursorPosition(pole.hand, n.coord);
	SetConsoleTextAttribute(pole.hand, n.color);
	cout << CharNyamka;
}

bool Nyamka::checkNyam(COORD c)
{
	bool res = false;
	for (vector<Nyam>::iterator it = vecNyam.begin(); it!=vecNyam.end(); ++it)
	{
		if (it->coord == c)
		{
			createNewNyam(it);
			res = true;
			break;
		}
	}
	return res;
}