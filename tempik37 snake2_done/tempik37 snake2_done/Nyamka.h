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
	struct Nyam
	{
		Nyam(){}
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

	Nyamka(Pole &p);
	
	bool checkNyam(COORD c, WORD &col); // всередині буде створювати нову нямку. повертає результат для Snake
	void setCountNyam(size_t cN) { countNyam = cN;}
	size_t getCountNyam() const { return countNyam; }
	size_t getScore() const { return gamePoints; }
	void init();
	void clear(){ vecNyam.clear();}
	void setPoleLink(Pole *p) { pole = p; }

	void setNyam(const Nyam & n)
	{
		vecNyam.push_back(n);
	}

	const Nyam & getNyam(size_t index)
	{
		return vecNyam[index];
	}

	void writeToFile(std::ofstream &f)
	{
		f.write((char*)&countNyam, sizeof(countNyam));
		f.write((char*)&gamePoints, sizeof(gamePoints));
	}
	void writeToFile(std::fstream &f)
	{
		f.write((char*)&countNyam, sizeof(countNyam));
		f.write((char*)&gamePoints, sizeof(gamePoints));
	}
	void readFromFile(std::ifstream &f)
	{
		f.read((char*)&countNyam, sizeof(countNyam));
		f.read((char*)&gamePoints, sizeof(gamePoints));
	}

	size_t getSizeSkip() const { return sizeof(countNyam)+sizeof(gamePoints); }

private:
	
	void writePoints(WORD col)
	{
		COORD co = { 0, pole->yMax + 3 };
		SetConsoleCursorPosition(pole->hand, co);
		SetConsoleTextAttribute(pole->hand, 7);
		cout << "Game Points: ";
		SetConsoleTextAttribute(pole->hand, col);
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
	
	size_t countNyam;  //початково задається кількість в конструкторі
	Pole *pole;
	static const char CharNyamka = '-';
	size_t gamePoints;
	vector<Nyam> vecNyam;
};

