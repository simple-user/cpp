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
		} while (p.chekCoord(x, y)); // ��������� ���� ����� ������

		
		p.setCoord(x, y, 1);
		vecNyam.emplace_back(x, y, 7, true); // ��-��! :)

	}

	showStartNyamki();
}

void Nyamka::createNewNyam(Nyam & nyam)
{
	if (!pole.isFree())
	{
		nyam.active = false;
		return; //���� ��� ���� ������ ������� �� � �� ������!
	}
	
	size_t x = 0;
	size_t y = 0;

	do
	{
		x = pole.xMin + rand() % pole.width;
		y = pole.yMin + rand() % pole.height;
	} while (pole.chekCoord(x, y)); // ��������� ���� ����� ������


	pole.setCoord(x, y, 1);
	 // ��-��! :)
	nyam.coord.X = x;
	nyam.coord.Y = y;
	nyam.color = 7;

	showOneNyam(nyam);
}

void Nyamka::showStartNyamki() const
{
	for (auto a : vecNyam)
	{
		showOneNyam(a);
	}
}

inline void Nyamka::showOneNyam(Nyam & n) const
{
	SetConsoleCursorPosition(pole.hand, n.coord);
	SetConsoleTextAttribute(pole.hand, n.color);
	cout << CharNyamka;
}

bool Nyamka::checkNyam(COORD c)
{
	bool res = false;
	for (auto &a : vecNyam)
	{
		if (a.coord == c && a.active==true)
		{
			// ������������ ������� ���� ���� ����� ������
			createNewNyam(a);
			res = true;
			break;
		}
	}
	return res;
}