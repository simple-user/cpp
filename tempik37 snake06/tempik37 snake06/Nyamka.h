#pragma once
#include <vector>
#include <Windows.h>
#include <ctime>
#include <exception>
#include <string>
#include "Pole.h"

using std::vector;
using std::exception;
using std::string;

enum ColorNyam {RED = 12, GREEN = 10, BLUE = 9, WHITE = 15};

class Nyamka
{
public:
	Nyamka(Pole &p);
	
	bool checkNyam(COORD c, WORD &col); // всередині буде створювати нову нямку. повертає результат для Snake
	void setCountNyam(size_t cN) { countNyam = cN;}
	size_t getCountNyam() { return countNyam; }
	void init();
	void clear(){ vecNyam.clear();}
private:
	struct Nyam
	{
		Nyam(size_t x, size_t y, WORD c)
		{
			coord.X = x;
			coord.Y = y;
			color = c;
		}
		Nyam(COORD cor, WORD col) : coord(cor), color(col){}
		
		COORD coord;
		WORD color;
	};

	
	void writePoints(WORD col)
	{
		COORD co = { 0, pole.yMax + 3 };
		SetConsoleCursorPosition(pole.hand, co);
		SetConsoleTextAttribute(pole.hand, 7);
		cout << "Game Points: ";
		SetConsoleTextAttribute(pole.hand, col);
		cout << gamePoints * 100 << "                                ";
	}

	size_t getColorNyam() const
	{
		size_t col[4] = { 12, 10, 9, 15 };
		return col[rand() % 4];
	}


	void createNewNyam(vector<Nyam>::iterator &itNyam);
	void showStartNyamki() const;
	inline void showOneNyam(Nyam n) const;
	
	vector<Nyam> vecNyam;
	size_t countNyam;  //початково задається кількість в конструкторі
	Pole &pole;
	static const char CharNyamka = 'Z';
	size_t gamePoints;
		
};

